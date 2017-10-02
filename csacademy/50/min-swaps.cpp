#if defined(LOCAL)
#define PROBLEM_NAME "min-swaps"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
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

l cost(vl& v) {
  l z = 0;
  F(i, 0, v.size() - 1) z += abs(v[i + 1] - v[i]);
  return z;
}

void solve(istream& cin, ostream& cout) {/*
  F(i, 1, 5) {
    vl v(i * 2);
    iota(all(v), 1);
    sort(all(v));
    l best = 0;
    do {
      best = max(best, cost(v));
    } while (next_permutation(all(v)));
    sort(all(v));
    do {
      if (cost(v) == best) cout << v << lf;
    } while (next_permutation(all(v)));
    }*/
  l tcc; cin >> tcc;
  while (tcc--) {
    l n; cin >> n;
    vl v(n); F(i, 0, n) cin >> v[i];
    l pa, pb;
    l m = n / 2;
    F(i, 0, n) {
      if (v[i] == m) pa = i;
      if (v[i] == m + 1) pb = i;
    }
    // a...b
    auto c = v;
    l t = 0;
    if (pa != 0) {swap(c[0], c[pa]); t++; if (pb == 0) pb = pa;}
    if (pb != n - 1) {swap(c[n - 1], c[pb]); t++; }
    F(i, 1, n - 1) {
      if (i % 2 and c[i] < m) t++;
    }
    l answer = t;
    // b..a
    F(i, 0, n) {
      if (v[i] == m) pb = i;
      if (v[i] == m + 1) pa = i;
    }
    c = v;
    t = 0;
    if (pa != 0) {swap(c[0], c[pa]); t++; if (pb == 0) pb = pa;}
    if (pb != n - 1) {swap(c[n - 1], c[pb]); t++; }
    F(i, 1, n - 1) {
      if (i % 2 == 0 and c[i] < m) t++;
    }
    answer = min(answer,t);
    cout << answer << lf;
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
