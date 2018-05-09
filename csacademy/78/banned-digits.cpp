#if defined(LOCAL)
#define PROBLEM_NAME "banned-digits"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define C(x, ...) ;
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
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

void solve(istream& cin, ostream& cout) {
  vl v(11); F(i, 0, 10) {
    l x; cin >> x; x = 1 - x;
    v[i + 1] = x;
  }
  F(i, 0, 10) v[i + 1] += v[i];
  l n; cin >> n;
  l allowed = v.back();
  l a19 = v[10] - v[1];
  vl d;
  l t = n;
  while (t) {
    d.emplace_back(t % 10);
    t /= 10;
  }
  l k = d.size();
  vl r(k + 1); // r[i] - # of ints with i-th digit <= d[i - 1]
  l p = 1;
  F(i, 0, k) {
    l x = d[i];
    t = 0;
    if (v[x + 1] - v[x]) { // x is allowed
      t += r[i];
    }
    if (i != k - 1) {
      t += max(l(0), v[x]) * p; // [0,x)...
    } else {
      t += max(l(0), v[x] - v[1]) * p; // (0,x)...
    }
    r[i + 1] = t;
    p *= allowed;
  }
  l sub = 0; // ___xxx
  p = 1;
  F(i, 1, k) {
    sub += a19 * p;
    p *= allowed;
  }
  if (v[1]) sub++;
  cout << sub + r.back() << lf;
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
