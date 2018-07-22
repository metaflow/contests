#if defined(LOCAL)
#define PROBLEM_NAME "c"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#include <bits/stdc++.h>
#endif

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
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

const l MOD = e9 + 7;

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

void solve(istream& cin, ostream& cout) {
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    cout << "Case #" << tc << ": ";
    l n, m; cin >> n >> m;
    vl h(n);
    l w, x, y, z;
    cin >> h[0] >> h[1] >> w >> x >> y >> z;
    F(i, 2, n) {
      h[i] = (w * h[i - 2] + x * h[i - 1] + y) % z;
    }
    vl from(m), to(m), up(m), down(m);
    l MAX = e9;
    vl du(n, MAX), dd(n, MAX);
    F(i, 0, m) {
      cin >> from[i] >> to[i] >> up[i] >> down[i];
      from[i]--;
      to[i]--;
      if (from[i] > to[i]) {
        swap(from[i], to[i]);
        swap(up[i], down[i]);
      }
      F(j, from[i], to[i]) {
        du[j] = min(du[j], up[i]);
        dd[j] = min(dd[j], down[i]);
      }
    }
    // L(du);
    // L(dd);
    l answer = binary_search_lower(0, z * 2, [&](l t) {
        l a = 0, b = e9;
        F(i, 0, n) {
          l c = max(a, 2 * h[i] - t);
          l d = min(b, 2 * h[i] + t);
          if (c > d) return false;
          a = max(l(0), c - dd[i] * 2);
          b = min(MAX, d + du[i] * 2);
        }
        return true;
      });
    cout << (answer / 2) << (answer % 2 ? ".5" : "") << lf;
  }
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
