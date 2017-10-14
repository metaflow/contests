#if defined(LOCAL)
#define PROBLEM_NAME "sum-triplets"
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
#define MAX(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__y:__x;})
#define MIN(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  l m = 0;
  vl v(n); F(i, 0, n) cin >> v[i];
  unordered_map<l, l> frq;
  vl u;
  for (auto i : v) {
    if (frq[i] == 0) u.emplace_back(i);
    m = max(m, i);
    frq[i]++;
  }
  sort(all(u));
  l answer = 0;
  F(i, 0, u.size()) {
    if (u[i] == 0) continue;
    if (frq.find(u[i] * 2) != frq.end()) {
      answer += frq[u[i] * 2] * frq[u[i]] * (frq[u[i]] - 1) / 2;
    }
    F(j, i + 1, u.size()) {
      if (u[i] + u[j] > m) break;
      if (frq.find(u[i] + u[j]) != frq.end()) {
        answer += frq[u[i]] * frq[u[j]] * frq[u[i] + u[j]];
      }
    }
  }
  if (u[0] == 0) {
    l t = frq[0];
    for (auto i : u) if (i) answer += t * frq[i] * (frq[i] - 1) / 2;
    answer += t * (t - 1) * (t - 2) / 6;
  }
  cout << answer << lf;
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
