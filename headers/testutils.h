#ifndef _TESTUTILS_H
#define _TESTUTILS_H

#include "logging.h"
#include "scope_guard.h"
#include "rnd.h"
#ifdef __GNUC__
#include <dirent.h>
#else
#include "win-dirent.h"
#endif
#include <unistd.h>
#include <cassert>
#include <future>
#include <iostream>
#include <vector>
#include "rusage.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"

void solve(std::istream& in, std::ostream& out);
std::function<bool(std::istream& hidden_state, std::istream& solver_out,
                   std::ostream& solver_in)>
    _judge;
std::function<bool(long long /* size */, std::ostream& /* out */)>
    _generate_random_test;
std::function<void(std::istream& /* in */, std::ostream& /* out */)>
    _solve_brute;
std::function<bool(std::istream& /* input */, std::istream& /* expected */,
                   std::istream& /* actual */, std::ostream& /* log */)>
    _custom_solution_checker;
namespace tst {
using namespace std;

#define TEST_LOG cerr
#define FIRST_ARG(x, ...) x
#define CHECK(x...)          \
  do {                       \
    if (FIRST_ARG(x)) break; \
    debug(x, #x);            \
    assert(0);               \
  } while (0);
const string  kPathSeparator("/");
static string test_problem_name;

struct _rusage {
  long long peak_memory;
};
atomic<bool> _test_in_progress;

bool _test_equal_double(double expected, double actual, double allowed_error) {
  using namespace std;
  const double e = 1E-15;
  if (abs(expected - actual) <= allowed_error + e) return true;
  double a = expected * (1.0 - allowed_error);
  double b = expected * (1.0 + allowed_error);
  if (a > b) swap(a, b);
  return (actual + e >= a) && (actual <= b + e);
}

string _str_to_lower(string s) {
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  return s;
}

bool _file_exist(string name) {
  ifstream f(name);
  return f.good();
}

void _copy_content(string from, string to) {
  ifstream f(from);
  ofstream t(to);
  char     c;
  while (f.get(c)) t.put(c);
}

vector<string> _tokenize_file(string fname) {
  using namespace std;
  vector<string> tokens;
  ifstream       f(fname);
  char           c;
  int            state = -1;  // 0 - word, 1 - space, 2 - endl
  string         t = "";
  while (f.get(c)) {
    int new_state;
    if (c == ' ') {
      new_state = 1;
    } else if (c == '\r') {
      continue;
    } else if (c == '\n') {
      new_state = 2;
      if (new_state == state) continue;
      c = '\n';
    } else {
      new_state = 0;
    }
    if (state == new_state) {
      t += c;
      continue;
    }
    state = new_state;
    if (not t.empty()) tokens.emplace_back(t);
    t = c;
  }
  if (not t.empty()) tokens.emplace_back(t);
  return tokens;
}

pair<double, bool> _try_strtod(string s) {
  using namespace std;
  const char* t = s.c_str();
  char*       e = nullptr;
  double      d = strtod(t, &e);
  if (e != t + s.size()) return make_pair(0, false);
  return make_pair(d, true);
}

pair<string, bool> _compare_lines(vector<string> ve, vector<string> va,
                                  ostream& out) {
  using namespace std;
  if (ve.size() != va.size()) {
    if (ve.size() == va.size() + 1 and ve.back() == " ") {
      out << " ignored space in expected output" << endl;
    } else {
      return make_pair("<>", false);
    }
  }
  int n = va.size();
  for (int i = 0; i < n; i++) {
    if (ve[i] == va[i]) continue;
    if (ve[i].find(".") == string::npos and ve[i].find(".") == string::npos) {
      return make_pair("<>", false);
    }
    auto de = _try_strtod(ve[i]);
    auto da = _try_strtod(va[i]);
    if (de.second and da.second) {
      if (va[i].find("e") != string::npos) {
        out << ' ' << va[i] << " is not a fixed double format" << endl;
      }
      if (_test_equal_double(de.first, da.first, _max_double_error)) {
        continue;
      }
      return make_pair("<> double", false);
    } else {
      return make_pair("<>", false);
    }
  }
  return make_pair("", true);
}

bool _compare_tokenized(vector<string>& /* input */, vector<string>& expected,
                        vector<string>& actual, ostream& out) {
  int                                   i = 0, j = 0;
  bool                                  ok = true;
  vector<tuple<string, string, string>> diff;
  while (i < expected.size() and j < actual.size()) {
    vector<string> le, la;
    while (i < expected.size() and expected[i] != "\n") {
      le.emplace_back(expected[i++]);
    }
    i++;
    while (j < actual.size() and actual[j] != "\n") {
      la.emplace_back(actual[j++]);
    }
    j++;
    auto c = _compare_lines(le, la, out);
    ok = ok and c.second;
    string se;
    for (auto s : le) se += s;
    string sa;
    for (auto s : la) sa += s;
    diff.emplace_back(se, sa, c.first);
  }
  ok = ok and i >= expected.size() and j >= actual.size() and
       not actual.empty() and actual.back() == "\n";
  if (ok) return true;
  while (i < expected.size()) {
    string s;
    while (i < expected.size() and expected[i] != "\n") s += expected[i++];
    i++;
    diff.emplace_back(s, "", "> missing");
  }
  while (j < actual.size()) {
    string s;
    while (j < actual.size() and actual[j] != "\n") s += actual[j++];
    j++;
    diff.emplace_back("", s, "< missing");
  }
  int we = 0, wa = 0;
  for (auto t : diff) {
    we = max(we, (int)get<0>(t).size());
    wa = max(wa, (int)get<1>(t).size());
  }
  we += 2;
  for (auto t : diff) {
    string s = get<0>(t);
    out << s;
    for (int k = (int)s.size(); k < we; k++) out << ' ';
    s = get<1>(t);
    out << s;
    for (int k = (int)s.size(); k < wa; k++) out << ' ';
    out << ' ' << get<2>(t) << '\n';
  }
  if (actual.empty() or actual.back() != "\n") {
    out << "no '\\n' at the end of output" << '\n';
  }
  return false;
}

bool _compare_output(string input_file_name, string out_expected,
                     string out_actual, long duration_ms, long max_duration_ms,
                     ostream& out) {
  stringstream ss;
  bool         ok;
  if (not _custom_solution_checker) {
    if (out_expected == "") {
      out << duration_ms << " ms";
      if (duration_ms > max_duration_ms) out << " TLE";
      cout << " output:" << '\n';
      ifstream f(out_actual);
      string   s;
      while (getline(f, s)) { out << s << '\n'; }
      return true;
    }
    auto input = (_tokenize_file(input_file_name));
    auto expected = (_tokenize_file(out_expected));
    auto actual = (_tokenize_file(out_actual));
    ok = _compare_tokenized(input, expected, actual, ss);
  } else {
    ifstream in(input_file_name);
    ifstream actual(out_actual);
    if (out_expected.empty()) {
      stringstream expected("expected output is not defined");
      ok = _custom_solution_checker(in, expected, actual, ss);
    } else {
      ifstream expected(out_expected);
      ok = _custom_solution_checker(in, expected, actual, ss);
    }
  }
  if (ok) {
    out << ": passed " << duration_ms << " ms";
    if (duration_ms > max_duration_ms) out << " TLE";
    out << endl << ss.str();
  } else {
    out << ": failed" << endl;
    out << endl << ss.str();
  }
  return ok;
}

string _read_last_input() {
  using namespace std;
  ifstream f(test_problem_name + ".testinfo");
  string   s;
  f >> s;
  return s;
}

void _write_last_input(string s) {
  using namespace std;
  string name = test_problem_name;
  name += ".testinfo";
  if (s.empty()) {
    remove(name.c_str());
  } else {
    ofstream f(name);
    f << s;
  }
}

set<string> _list_files(string path) {
  set<string>    files;
  DIR*           dir;
  struct dirent* ent;
  if ((dir = opendir(path.c_str())) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type != DT_REG) continue;
      string s = ent->d_name;
      files.emplace(s);
    }
    closedir(dir);
  } else {
    perror("");
  }
  return files;
}

set<string> _filter_files(set<string> files) {
  set<string> result;
  string      name = test_problem_name;
  for (auto s : files) {
    if (s.find(name) != 0) continue;
    result.emplace(s);
  }
  return result;
}

_rusage _monitor_rusage(long long max_allowed_memory, long long max_time_ms) {
  _rusage r;
  using namespace std::chrono;
  auto t1 = high_resolution_clock::now();
  r.peak_memory = 0;
  while (_test_in_progress) {
    r.peak_memory = getPeakRSS();
    if (r.peak_memory > max_allowed_memory) {
      TEST_LOG << "\nerror: memory usage " << fixed << setprecision(2)
               << (double)r.peak_memory / 1024 / 1024 << " Mb is greater than "
               << fixed << setprecision(2)
               << (double)max_allowed_memory / 1024 / 1024 << " Mb" << endl;
      TEST_LOG << "use `#define MEMORY <MB>` to set limit" << endl;
      exit(1);
    }
    usleep(1000);
    auto t2 = high_resolution_clock::now();
    long ms = duration_cast<milliseconds>(t2 - t1).count();
    if (ms > max_time_ms) {
      TEST_LOG << "\nerror: running longer than " << max_time_ms << " ms"
               << endl;
      TEST_LOG << "use `#define TIME <seconds>` to set limit" << endl;
      exit(1);
    }
  }
  return r;
}

class threadbuf : public std::streambuf {
 private:
  typedef std::streambuf::traits_type traits_type;
  typedef std::string::size_type      string_size_t;

  std::mutex              d_mutex;
  std::condition_variable d_condition;
  std::string             d_out;
  std::string             d_in;
  std::string             d_tmp;
  char*                   d_current;
  bool                    d_closed;
  function<void(char)>    on_output;

 public:
  threadbuf(string_size_t out_size = 1024, string_size_t in_size = 1024)
      : d_out(std::max(string_size_t(1), out_size), ' '),
        d_in(std::max(string_size_t(1), in_size), ' '),
        d_tmp(std::max(string_size_t(1), in_size), ' '),
        d_current(&this->d_tmp[0]),
        d_closed(false) {
    this->setp(&this->d_out[0], &this->d_out[0] + this->d_out.size() - 1);
    this->setg(&this->d_in[0], &this->d_in[0], &this->d_in[0]);
  }

  void set_on_output(function<void(char)> f) { on_output = f; }
  void close() {
    {
      std::unique_lock<std::mutex> lock(this->d_mutex);
      this->d_closed = true;
      while (this->pbase() != this->pptr()) { this->internal_sync(lock); }
    }
    this->d_condition.notify_all();
  }

 private:
  int_type underflow() {
    if (this->gptr() == this->egptr()) {
      std::unique_lock<std::mutex> lock(this->d_mutex);
      while (&this->d_tmp[0] == this->d_current && !this->d_closed) {
        this->d_condition.wait(lock);
      }
      if (&this->d_tmp[0] != this->d_current) {
        std::streamsize size(this->d_current - &this->d_tmp[0]);
        traits_type::copy(this->eback(), &this->d_tmp[0],
                          this->d_current - &this->d_tmp[0]);
        if (on_output) {
          for (auto i = &d_tmp[0]; i != d_current; i++) { on_output(*i); }
        }
        this->setg(this->eback(), this->eback(), this->eback() + size);
        this->d_current = &this->d_tmp[0];
        this->d_condition.notify_one();
      }
    }
    return this->gptr() == this->egptr()
               ? traits_type::eof()
               : traits_type::to_int_type(*this->gptr());
  }
  int_type overflow(int_type c) {
    std::unique_lock<std::mutex> lock(this->d_mutex);
    if (!traits_type::eq_int_type(c, traits_type::eof())) {
      *this->pptr() = traits_type::to_char_type(c);
      this->pbump(1);
    }
    return this->internal_sync(lock) ? traits_type::eof()
                                     : traits_type::not_eof(c);
  }
  int sync() {
    std::unique_lock<std::mutex> lock(this->d_mutex);
    return this->internal_sync(lock);
  }
  int internal_sync(std::unique_lock<std::mutex>& lock) {
    char* end(&this->d_tmp[0] + this->d_tmp.size());
    while (this->d_current == end && !this->d_closed) {
      this->d_condition.wait(lock);
    }
    if (this->d_current != end) {
      std::streamsize size(
          std::min(end - d_current, this->pptr() - this->pbase()));
      traits_type::copy(d_current, this->pbase(), size);
      this->d_current += size;
      std::streamsize remain((this->pptr() - this->pbase()) - size);
      traits_type::move(this->pbase(), this->pptr(), remain);
      this->setp(this->pbase(), this->epptr());
      this->pbump(remain);
      this->d_condition.notify_one();
      return 0;
    }
    return traits_type::eof();
  }
};

bool run_interactive_judge(istream& in, ostream& out) {
  atomic<int> turn(0);
  threadbuf   a;
  a.set_on_output([&](char c) {
    if (turn != 1) {
      turn = 1;
      out << "";
    }
    out << c;
  });
  std::ostream a_out(&a);
  std::istream a_in(&a);
  threadbuf    b;
  b.set_on_output([&](char c) {
    if (turn != 2) {
      turn = 2;
      out << "> ";
    }
    out << c;
  });
  std::ostream b_out(&b);
  std::istream b_in(&b);
  auto         x = async(launch::async, _judge, ref(in), ref(a_in), ref(b_out));
  // thread       t(&solve, ref(b_in), ref(a_out));

  // TODO: why do we running solve in thread?
  //auto         y = async(launch::async, solve, ref(b_in), ref(a_out));
  solve(ref(b_in), ref(a_out));
  bool z = x.get();
  // y.wait();
  out.flush();
  return z;
}

bool _run_tests() {
  _test_in_progress = true;
  set<string> files = _filter_files(_list_files("."));

  string name = test_problem_name;

  vector<tuple<int, string, string>> cases;
  string                             last = _read_last_input();
  for (auto f : files) {
    // problem\.in(.*)
    string t = name + ".in";
    int    weight = (f == last) ? 0 : 1;
    if (f.find(t) == 0) {
      string o = name + ".out" + f.substr(t.size());
      if (files.count(o)) {
        cases.emplace_back(weight, f, o);
      } else {
        cases.emplace_back(weight, f, "");
      }
      continue;
    }
    // problem(.*)in
    if (f.size() > 2 and f.substr(f.size() - 2) == "in") {
      string o = f.substr(0, f.size() - 2) + "out";
      if (files.count(o)) {
        cases.emplace_back(weight, f, o);
      } else {
        cases.emplace_back(weight, f, "");
      }
    }
  }
  sort(cases.begin(), cases.end());

  string failure;
  bool   ok = true;

  long long max_allowed_memory = 1024;
#if defined(MEMORY)
  max_allowed_memory = MEMORY;
#endif
  max_allowed_memory *= 1024 * 1024;
  long long max_time = 10;
#if defined(TIME)
  max_time = TIME;
#endif
  max_time *= 1000;

  auto usage = async(launch::async, &_monitor_rusage, max_allowed_memory,
                     max_time * (cases.size() + 1));
  for (auto c : cases) {
    TEST_LOG << get<1>(c) << ' ';
    ifstream fin(get<1>(c));
    string   o = name + ".output";
    ofstream fout(o);
    using namespace std::chrono;
    auto t1 = high_resolution_clock::now();
    if (_judge) {
      if (!run_interactive_judge(fin, fout)) {
        ok = false;
        if (failure.empty()) failure = get<1>(c);
      }
      continue;
    }
    solve(fin, fout);
    auto t2 = high_resolution_clock::now();
    long ms = duration_cast<milliseconds>(t2 - t1).count();
    fin.close();
    fout.close();
    if (_compare_output(get<1>(c), get<2>(c), o, ms, max_time, TEST_LOG)) {
      remove(o.c_str());
      continue;
    }
    ok = false;
    if (failure.empty()) failure = get<1>(c);
  }
  _write_last_input(failure);
  _test_in_progress = false;
  auto u = usage.get();
  TEST_LOG << "peak memory " << fixed << setprecision(2)
           << (double)u.peak_memory / 1024 / 1024 << " Mb" << endl;
  return ok;
}

void _random_test() {
  assert(_generate_random_test);
  assert(_custom_solution_checker or _solve_brute or _judge);
  // TODO: brute and interactive judge interaction
  string input_file_name = test_problem_name + ".rndinput";
  string expected_output = test_problem_name + ".rndoutput";
  string actual_output = test_problem_name + ".output";
  for (int tc = 0;; tc++) {
    bool ok = true;
    bool compare_output = true;
    bool write_out = false;
    {
      ofstream in(input_file_name);
      if (not _generate_random_test(tc, in)) break;
    }
    {
      ifstream in(input_file_name);
      ofstream out(actual_output);
      if (_judge) {
        ok = run_interactive_judge(in, out);
        compare_output = false;
        write_out = !ok;
      } else {
        solve(in, out);
      }
    }
    stringstream ss;
    if (_solve_brute) {
      ifstream in(input_file_name);
      ofstream out(expected_output);
      write_out = true;
      _solve_brute(in, out);
    }
    if (compare_output) {
      if (_custom_solution_checker) {
        ifstream in(input_file_name);
        ifstream actual(actual_output);
        if (_solve_brute) {
          ifstream expected(expected_output);
          ok = _custom_solution_checker(in, expected, actual, ss);
        } else {
          stringstream expected("_solve_brute is not defined");
          ok = _custom_solution_checker(in, expected, actual, ss);
        }
      } else {
        ok =
            _compare_output("random", expected_output, actual_output, 0, 0, ss);
      }
    }
    if (ok) continue;
    // found new failed test case
    int    i = 1;
    string name_in = test_problem_name + ".in" + to_string(i);
    string name_out = test_problem_name + ".out" + to_string(i);
    while (1) {
      name_in = test_problem_name + ".in" + to_string(i);
      name_out = test_problem_name + ".out" + to_string(i);
      if (not _file_exist(name_in) and not _file_exist(name_out)) {
        _copy_content(input_file_name, name_in);
        if (write_out) { _copy_content(expected_output, name_out); }
        break;
      }
      i++;
    }
    TEST_LOG << ss.str() << '\n';
    TEST_LOG << name_in;
    if (_solve_brute) TEST_LOG << ' ' << name_out;
    TEST_LOG << " created\n";
    remove(input_file_name.c_str());
    remove(actual_output.c_str());
    remove(expected_output.c_str());
    return;
  }
  remove(input_file_name.c_str());
  remove(expected_output.c_str());
  remove(actual_output.c_str());
  TEST_LOG << "random: passed" << '\n';
}

void maybe_run_tests(istream& in, ostream& out) {
  auto run = getenv("RUN_TESTS");
  if (run) {
    int n = atoi(run);
    if (n % 2) _run_tests();
    if ((n >> 1) % 2) {
      if (_generate_random_test and
          (_custom_solution_checker or _solve_brute or _judge)) {
        _random_test();
      } else {
        TEST_LOG << "set _generate_random_test\n"
                 << "and _custom_solution_checker or _solve_brute or _judge\n"
                 << "for random test\n";
      }
    }
  } else {
    solve(in, out);
  }
}

void test_init(int argc, char** argv) {
  if (argc > 0) {
    string s(argv[0]);
    auto   p = s.rfind(kPathSeparator);
    string name = s;
    if (p + 1 < s.size()) name = s.substr(p + 1);
    test_problem_name = name;
  }
}
}  // namespace tst
#pragma clang diagnostic pop
#endif  // TESTUTILS_H
