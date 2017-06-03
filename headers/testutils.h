#ifndef _TESTUTILS_H
#define _TESTUTILS_H
#include "prettyprint.h"
// #include "testlib.h"
#include "dirent.h"
#include <bits/stdc++.h>

using namespace std;
#define TEST_LOG cerr
void solve(std::istream& in, std::ostream& out);

bool _test_equal_double(double expected, double actual, double allowed_error) {
  using namespace std;
  const double e = 1E-15;
  if (abs(expected - actual) <= allowed_error + e) return true;
  // Is x or y too close to zero?
  // if (abs(x) < EPS || abs(y) < EPS) return false;
  // Check relative precision.
  // return (abs((x - y) / x) < EPS) && (abs((x - y) / y) < EPS);
  double a = expected * (1.0 - allowed_error);
  double b = expected * (1.0 + allowed_error);
  if (a > b) swap(a, b);
  return (actual + e >= a) && (actual <= b + e);
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

bool _compare_output(string in, string out_expected, string out_actual) {
  using namespace std;
  TEST_LOG << in;
  if (out_expected == "") {
    TEST_LOG << " output:" << '\n';
    ifstream f(out_actual);
    string s;
    while (getline(f, s)) {
      TEST_LOG << s << '\n';
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
    TEST_LOG << ": passed\n";
    return true;
  }
  TEST_LOG << ": failed\n";
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
    TEST_LOG << s;
    for (int k = (int)s.size(); k < we; k++) TEST_LOG << ' ';
    s = get<1>(t);
    TEST_LOG << s;
    for (int k = (int)s.size(); k < wa; k++) TEST_LOG << ' ';
    TEST_LOG << ' ' << get<2>(t) << '\n';
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
    solve(fin, fout);
    fin.close();
    fout.close();
    if (_compare_output(get<1>(c), get<2>(c), o)) continue;
    if (failure.empty()) failure = get<1>(c);
  }
  _write_last_input(failure);
}

void maybe_run_tests(istream& in, ostream& out) {
  auto run = getenv("RUN_TESTS");
  if (run) {
    _run_tests();
  } else {
    solve(in, out);
  }
}

#endif
