#if defined(LOCAL)
#define PROBLEM_NAME "E"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
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
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  vll events; // (t, i) i - added, (t, -i) - i removed
  vb required(n);
  F(i, 0, n) {
    l a, b; cin >> a >> b;
    events.emplace_back(a, i + 1);
    events.emplace_back(b + 1, -i - 1);
  }
  sort(all(events));
  unordered_set<l> active;
  l p = 0;
  while (p < events.size()) {
    l t = events[p].first;
    while (p < events.size() and events[p].first == t) {
      if (events[p].second > 0) {
        active.emplace(events[p].second - 1);
      } else {
        active.erase(abs(events[p].second) - 1);
      }
      p++;
    }
    if (active.size() == 1) {
      required[*active.begin()] = true;
    }
  }
  F(i, 0, n) {
    if (not required[i]) {
      cout << i + 1 << lf;
      return;
    }
  }
  cout << -1 << lf;
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
