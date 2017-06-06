#ifndef _TESTUTILS_H
#define _TESTUTILS_H
#include "rnd.h"
#include "prettyprint.h"
#include "dirent.h"
#include <bits/stdc++.h>

using namespace std;
#define TEST_LOG cerr
void solve(std::istream& in, std::ostream& out);

bool _test_equal_double(double expected, double actual, double allowed_error) {
  using namespace std;
  const double e = 1E-15;
  if (abs(expected - actual) <= allowed_error + e) return true;
  double a = expected * (1.0 - allowed_error);
  double b = expected * (1.0 + allowed_error);
  if (a > b) swap(a, b);
  return (actual + e >= a) && (actual <= b + e);
}


bool _file_exist(string name) {
  ifstream f(name);
  return f.good();
}

void _copy_content(string from, string to) {
  ifstream f(from);
  ofstream t(to);
  char c;
  while (f.get(c)) t.put(c);
}

vector<string> _tokenize_file(string fname) {
  using namespace std;
  vector<string> tokens;
  ifstream f(fname);
  char c;
  int state = -1; // 0 - word, 1 - space, 2 - endl
  string t = "";
  while (f.get(c)) {
    int new_state;
    if (c == ' ') {
      new_state = 1;
    } else if (c == '\r' or c == '\n') {
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
  char* e = nullptr;
  double d = strtod(t, &e);
  if (e != t + s.size()) return make_pair(0, false);
  return make_pair(d, true);
}

pair<string, bool> _compare_lines(vector<string> ve, vector<string> va) {
  using namespace std;
  if (ve.size() != va.size()) return make_pair("<>", false);
  int n = ve.size();
  for(int i = 0; i < n; i++) {
    if (ve[i] == va[i]) continue;
    if (ve[i].find(".") == string::npos and ve[i].find(".") == string::npos) {
      return make_pair("<>", false);
    }
    auto de = _try_strtod(ve[i]);
    auto da = _try_strtod(va[i]);
    if (de.second and da.second) {
      if (va[i].find("e") != string::npos) {
        TEST_LOG << '\n' << "WARN: " << va[i] << " is not a fixed double format" << '\n';
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

bool _compare_output(string in, string out_expected, string out_actual,
                     long duration_ms, ostream& out) {
  out << in;
  if (out_expected == "") {
    out << " output:" << '\n';
    ifstream f(out_actual);
    string s;
    while (getline(f, s)) {
      out << s << '\n';
    }
    return true;
  }
  auto expected = (_tokenize_file(out_expected));
  auto actual = (_tokenize_file(out_actual));
  int i = 0, j = 0;
  bool ok = true;
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
    auto c = _compare_lines(le, la);
    ok = ok and c.second;
    string se; for (auto s : le) se += s;
    string sa; for (auto s : la) sa += s;
    diff.emplace_back(se, sa, c.first);
  }
  ok = ok and i >= expected.size() and j >= actual.size() and
             not actual.empty() and actual.back() == "\n";
  if (ok) {
    out << ": passed " << duration_ms << " ms" << endl;
    return true;
  }
  out << ": failed\n";
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
    we = max(we, (int) get<0>(t).size());
    wa = max(wa, (int) get<1>(t).size());
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
    TEST_LOG << "no '\n' and the end of output" << '\n';
  }
  return false;
}

string _read_last_input() {
  using namespace std;
  string name = PROBLEM_NAME;
  ifstream f(name + ".testinfo");
  string s;
  f >> s;
  return s;
}

void _write_last_input(string s) {
  using namespace std;
  string name = PROBLEM_NAME;
  ofstream f(name + ".testinfo");
  f << s;
}

set<string> _list_files(string path) {
  set<string> files;
  DIR *dir;
  struct dirent *ent;
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
  string name(PROBLEM_NAME);
  for (auto s : files) {
    if (s.find(name) != 0) continue;
    result.emplace(s);
  }
  return result;
}

void _run_tests() {
  set<string> files = _filter_files(_list_files("."));

  string name(PROBLEM_NAME);

  vector<tuple<int, string, string>> cases;
  string last = _read_last_input();
  for (auto f : files) {
    // problem\.in(.*)
    string t = name + ".in";
    int w = (f == last) ? 0 : 1;
    if (f.find(t) == 0) {
      string o = name + ".out" + f.substr(t.size());
      if (files.count(o)) {
        cases.emplace_back(w, f, o);
      } else {
        cases.emplace_back(w, f, "");
      }
      continue;
    }
    // problem(.*)in
    if (f.size() > 2 and f.substr(f.size() - 2) == "in") {
      string o = f.substr(0, f.size() - 2) + "out";
      if (files.count(o)) {
        cases.emplace_back(w, f, o);
      } else {
        cases.emplace_back(w, f, "");
      }
    }
  }
  sort(cases.begin(), cases.end());

  string failure;
  for (auto c : cases) {
    ifstream fin(get<1>(c));
    string o = name + ".output";
    ofstream fout(o);
    using namespace std::chrono;
    auto t1 = high_resolution_clock::now();
    solve(fin, fout);
    auto t2 = high_resolution_clock::now();
    long ms = duration_cast<milliseconds>(t2 - t1).count();
    fin.close();
    fout.close();
    if (_compare_output(get<1>(c), get<2>(c), o, ms, TEST_LOG)) continue;
    if (failure.empty()) failure = get<1>(c);
  }
  _write_last_input(failure);
}

#if defined(RANDOM_TEST)
void generate(long long size, ostream& out);
void solve_brute(istream& cin, ostream& cout);

int _random_test_size_from = 1;
int _random_test_size_to = 20;
int _random_test_count = 100;
void _random_test() {
  string problem_name = PROBLEM_NAME;
  string input_file_name = problem_name + ".in.random";
  string expected_output = problem_name + ".out.random";
  string actual_output = problem_name + ".output";
  for (int size = _random_test_size_from; size < _random_test_size_to; size++) {
    cerr << '.';
    for (int tc = 0; tc < _random_test_count; tc++) {
      {
        ofstream in(input_file_name);
        generate(size, in);
      }
      {
        ifstream in(input_file_name);
        ofstream out(actual_output);
        solve(in, out);
      }
      {
        ifstream in(input_file_name);
        ofstream out(expected_output);
        solve_brute(in, out);
      }
      stringstream ss;
      if (_compare_output("random", expected_output, actual_output, 0, ss)) {
        continue;
      }
      // create new test case
      int i = 1;
      string name_in = problem_name + ".in" + to_string(i);
      string name_out = problem_name + ".out" + to_string(i);
      while (1) {
        name_in = problem_name + ".in" + to_string(i);
        name_out = problem_name + ".out" + to_string(i);
        if (not _file_exist(name_in) and not _file_exist(name_out)) {
          _copy_content(input_file_name, name_in);
          _copy_content(expected_output, name_out);
          break;
        }
        i++;
      }
      cerr << ss.str() << '\n';
      cerr << name_in << ' ' << name_out << " created\n";
      return;
    }
  }
  cerr << "random: passed" << '\n';
}
#endif

void maybe_run_tests(istream& in, ostream& out) {
  auto run = getenv("RUN_TESTS");
  if (run) {
    _run_tests();
#if defined(RANDOM_TEST)
    _random_test();
#endif
  } else {
    solve(in, out);
  }
}

#endif
