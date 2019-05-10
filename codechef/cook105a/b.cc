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
#include <cassert>  // TODO: template
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
bool interactive_judge(istream &, istream &, ostream &);
bool generate_random(l, ostream &);
bool solution_checker(istream &, istream &, istream &, ostream &);
int  main(int argc, char **argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  tst::test_init(argc, argv);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _judge = interactive_judge;
  // _custom_solution_checker = solution_checker;
  tst::maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
const l MOD = e9 + 7;  // end of template

void solve(istream &in, ostream &out) {
  l tcc;
  in >> tcc;
  while (tcc--) {
    l n;
    in >> n;
    bool ok = true;
    {
      l t = n;
      while (t % 2 == 0) {
        ok = !ok;
        t /= 2;
      }
    }
    if (ok) {
      out << "Win" << endl;
      while (n != 1) {
        L(n);
        if (n % 2) {
          l t = n;
          l x = 0;
          while (t % 2 == 1) {
            x++;
            t /= 2;
          }
          if (x == 1) {
            l k = 0;
            while (t and t % 2 == 0) {
              t /= 2;
              k++;
            }
            if (k % 2) {
              out << "+1" << endl;
              n++;
            } else {
              out << "-1" << endl;
              n--;
            }
          } else {
            out << "-1" << endl;
            n--;
          }
        } else {
          out << "/2" << endl;
          n /= 2;
        }
        string s;
        in >> s;
        if (s == "/2") { n /= 2; }
        if (s == "-1") { n--; }
        if (s == "+1") { n++; }
      }
      out << "-1" << endl;
      {
        string s;
        in >> s;
        if (s != "GG") return;
        continue;
      }
    } else {
      out << "Lose" << endl;
      string s;
      in >> s;
      if (s != "GG") return;
    }
  }
}
