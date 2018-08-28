#if defined(LOCAL)
#define PROBLEM_NAME "b"
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
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <limits>
#include <numeric>

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = 3.1415926;
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

const l MOD = e9 + 7; // end of template

// finds lowest x: f(x) = true, x within [a, b), b if f(b - 1) = false
l binary_search_lower(l a, l b, function<bool(l)> f) {
  l count = b - a;
  while (count > 0) {
    l step = count / 2;
    l m = a + step;
    if (f(m)) {
      count = step;
    } else {
      a = m + 1;
      count -= step + 1;
    }
  }
  return a;
}

// finds lowest x: f(x) = true, x within [a, b)
double binary_search_lower_double(double a, double b, function<bool(double)> f) {
  double diff = b - a;
  while (diff > EPS) {
    diff /= 2;
    double m = a + diff;
    if (!f(m)) a = m;
  }
  return a;
}

void solve(istream& in, ostream& out) {
  l n; in >> n;
  vl v(n);
  F(i, 0, n) in >> v[i];
  auto s = v;
  sort(all(s));
  vl bb(n);
  l T = n * (n + 1) / 2;
  out << s[binary_search_lower(0, n, [&](l k) {
        l x = s[k];
        I(k, x);
        F(i, 0, n) bb[i] = v[i] <= x ? -1 : 1;
        vl cc(n * 2 + 1);
        l off = n;
        cc[off] = 1;
        l good = 1;
        l sum = 0;
        l z = 0;
        F(i, 0, n) {
          //
          l t = sum + bb[i];
          if (bb[i] == 1) {
            good += cc[sum + 1 + off];
          } else {
            C(bb[i] == -1);
            good -= cc[sum + off];
          }
          C(good >= 0, good);
          z += good;
          sum = t;
          cc[sum + off]++;
          good++;
          /*/
          l t = sum + bb[i];
          good = 0;
          F(j, 0, t + 1 + off) good += cc[j];
          z += good;
          sum = t;
          cc[sum + off]++;
          //*/
        }
        I(bb, cc);
        return I(T - z, z) > z;
      })] << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
