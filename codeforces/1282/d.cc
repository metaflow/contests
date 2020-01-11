#if defined(LOCAL)
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#endif
#include <math.h>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using ii = pair<int, int>;
using lu = unsigned long long;
using l = long long;
using vs = vector<string>;
using vii = vector<ii>;
using vl = vector<l>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vlu = vector<lu>;
using ll = pair<l, l>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vvvb = vector<vvb>;
using vd = vector<double>;
using vvd = vector<vd>;
using mll = unordered_map<l, l>;
using sl = unordered_set<l>;
const l      INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const double PI = 3.14159265358979323846;
const l      e0 = 1, e3 = 1000, e5 = 100000, e6 = 10 * e5, e7 = 10 * e6,
        e8 = 10 * e7, e9 = 10 * e8, l0 = 0, l1 = 1, l2 = 2;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a, b, c) for (l a = l(b); a < l(c); a++)
#define B(a, b, c) for (l a = l(c) - 1; a >= l(b); a--)

void solve(istream &in, ostream &out);
void solve_brute(istream &, ostream &);

default_random_engine source(
    chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
}

bool random_bool() { return random_in_range(0, 2) == 1; }

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) { s += an[random_in_range(0, an.size())]; }
  return s;
}

// return false to stop
bool generate_random(l tc, ostream &out) {
  l max_cases = 20000;
  if (tc % (max_cases / 100) == 0) cerr << (tc * 100 / max_cases) << "%\r";
  if (tc <= 300) {
    out << string(max(l1, tc), 'a');
  } else if (tc <= 600) {
    out << string(tc - 300, 'b');
  } else {
    l      n = tc % 300 + 1;
    string s(n, 'a');
    F(i, 0, n) s[i] = random_bool() ? 'a' : 'b';
    out << s << lf;
  }
  return tc < max_cases;
}

bool interactive_judge(istream &hidden_state, istream &in, ostream &out) {
  // TODO: add conditional output for judge when there is an error.
  string s;
  hidden_state >> s;
  l n = s.size();
  cerr << "hidden " << s << endl;
  l k = 0;
  while (1) {
    string x;
    in >> x;
    k++;
    cerr << k << ' ' << x << endl;
    if (k > n + 2) {
      cerr << "too many tries" << endl;
      return false;
    }
    if (x == s) {
      out << 0 << endl;
      cerr << "OK" << endl << endl;
      return true;
    }
    if (x.size() == 1) {
      bool ok = false;
      F(i, 0, n) ok = ok or (s[i] == x[0]);
      if (ok) {
        out << n - 1 << endl;
      } else {
        out << n << endl;
      }
    } else {
      l d = 0;
      if (x.size() != s.size()) {
        if (x.size() == n + 1 && x.size() <= 300) {
          out << n + 1 << endl;
          continue;
        }
        cerr << "size mismatch" << endl;
        cerr << x.size() << ' ' << s.size() << endl;
        return false;
      }
      F(i, 0, n) if (x[i] != s[i]) d++;
      out << d << endl;
    }
  }
}

bool generate_random(l, ostream &);
bool solution_checker(istream &, istream &, istream &, ostream &);
int  main(int argc, char **argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  tst::test_init(argc, argv);
  _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  _judge = interactive_judge;
  // _custom_solution_checker = solution_checker;
  tst::maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
const l MOD = e9 + 7;  // end of template

void solve(istream &in, ostream &out) {
  auto ask = [&](string s) {
    out << s << endl;
    l x;
    in >> x;
    return x;
  };
  l a = ask("a");
  if (a == 0) return;
  l      p = 0;
  l      n = a + 1;
  if (a == 300) {
    auto x = ask(string(300, 'b'));
    assert(x != 0);
    return;
  }
  string s(n, 'a');
  l      d = ask(s);
  if (d > a) {
    s = string(a, 'b');
    l x = ask(s);
    if (x != 0) { x = 1 / (n - s.size()); }
    return;
  }
  while (d != 0) {
    if (n - p == d) {
      // invert all other symbols;
      F(i, p, n) s[i] = 'b';
      l x = ask(s);
      if (x != 0) { x = 1 / (n - s.size()); }
      break;
    }
    s[p] = 'b';
    l t = ask(s);
    if (t > d)
      s[p] = 'a';
    else
      d = t;
    p++;
  }
}
