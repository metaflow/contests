#if defined(LOCAL)
#define PROBLEM_NAME "F"
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

// returns (x, f(x)): f(x) = min(f(y)): y in [from, to]
ll ternary_search_min(l from, l to, function<l(l)> f) {
  l L = from, R = to;
  l rl = f(L), rr = f(R);
  while (1) {
    if (R - L < 2) {
      if (rl < rr) return make_pair(L, rl);
      return make_pair(R, rr);
    }
    if (R - L == 2) {
      l t = f(L + 1);
      if (t < rl) {
        if (t < rr) return make_pair(L + 1, t);
        return make_pair(R, rr);
      } else {
        if (rl < rr) return make_pair(L, rl);
        return make_pair(R, rr);
      }
    }
    l m1 = L + (R - L) / 3;
    l m2 = L + 2 * (R - L) / 3;
    vl v = {rl, f(m1), f(m2), rr};
    l x = 0;
    F(i, 1, 4) if (v[i] < v[x]) x = i;
    if (x < 2) { R = m2; rr = v[2]; }
    else { L = m1; rl = v[1]; }
  }
  assert(false);
  return make_pair(0, 0);
}

l dfs(vl& x, vll& y, l xa, l xb, l ya, l yb, vl& accx, vl& accy) {
  if (yb - ya == 1) {
    auto a = x.begin() + xa;
    auto b = x.begin() + xb;
    l p = y[ya].first;
    auto m = lower_bound(a, b, p);
    l xm = distance(x.begin(), m);
    return p * (xm - xa) - (accx[xm] - accx[xa])
      + (accx[xb] - accx[xm]) - p *(xb - xm);
  }
  if (xb - xa < 1) return 0;
  l ym = (ya + yb) / 2;
  auto t = ternary_search_min(
                              max(xa, xb - (accy[yb] - accy[ym])),
                              min(xb, xa + (accy[ym] - accy[ya])),
                              [&](l p) {
      return dfs(x, y, xa, p, ya, ym, accx, accy) +
      dfs(x, y, p, xb, ym, yb, accx, accy);
    });
  assert(t.second != INF);
  return t.second;
}

void solve(istream& cin, ostream& cout) {
  l n, m;
  cin >> n >> m;
  vl x(n); F(i, 0, n) cin >> x[i];
  sort(all(x));
  vll y(m); // (coord * capacity)
  F(i, 0, m) cin >> y[i].first >> y[i].second;
  sort(all(y));
  vl accx(n + 1) /* sum of coords */, accy(m + 1) /* capacity */;
  F(i, 0, n) accx[i + 1] = accx[i] + x[i];
  F(i, 0, m) accy[i + 1] = accy[i] + y[i].second;
  if (accy[m] < n) {
    cout << "-1" << lf;
    return;
  }
  cout << dfs(x, y, 0, n, 0, m, accx, accy) << lf;
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
