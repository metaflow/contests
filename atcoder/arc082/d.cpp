#if defined(LOCAL)
#define PROBLEM_NAME "d"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x...) (x)
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

struct Flip {
  l time, low, low_value, delta, high, high_value, d;
};

Flip next_flip(const Flip& f, l t, l m) {
  Flip next;
  next.time = t;
  l d = f.d * (next.time - f.time);
  next.d = -f.d;
  next.low = max(f.low, - d - f.delta);
  next.low_value = min(m, max(l(0), f.low_value + d));
  next.delta = f.delta + d;
  next.high = min(f.high, m - f.delta - d);
  next.high_value = min(m, max(l(0), f.high_value + d));
  return next;
}

void solve(istream& cin, ostream& cout) {
  l m; cin >> m;
  Flip f;
  f.time = 0;
  f.low = 0; f.low_value = 0;
  f.high = m; f.high_value = m;
  f.delta = 0;
  f.d = -1;
  l n; cin >> n;
  vector<Flip> ff(n + 2);
  ff[0] = f;
  F(i, 0, n) {
    l t; cin >> t;
    f = next_flip(f, t, m);
    ff[i + 1] = f;
  }
  ff[n + 1] = next_flip(f, e9 * 2, m);
  F(i, 0, n + 1) {
    // cerr << ff[i].time << " (" << ff[i].low << ' ' << ff[i].low_value << ") ("
         // << ff[i].high << ' ' <<  ff[i].high_value <<  ") " <<  ff[i].delta << endl;
  }
  l k; cin >> k;
  while (k--) {
    l t, a; cin >> t >> a;
    auto p = upper_bound(all(ff), t, [](l y, const Flip& x) {
        return y < x.time;
      });
    p--;
    if (a <= p->low) {
      a = p->low_value;
    } else if (a >= p->high) {
      a = p->high_value;
    } else {
      a += p->delta;
    }
    a += p->d * (t - p->time);
    a = min(m, max(l(0), a));
    cout << a << lf;
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
