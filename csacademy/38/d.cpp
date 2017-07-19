#if defined(LOCAL)
#define PROBLEM_NAME "d"
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

#if defined(LOCAL)
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#endif

l walk(l from, l to, l level, vl& allowed, vl& answer) {
  if (level >= allowed.size()) return from / 2 - 1;
  l x = walk(from * 2, to * 2 + 1, level + 1, allowed, answer);
  // L(from, to, x, level);
  if (allowed[level]) {
    F(i, 0, allowed[level]) {
      if (x < to) {
        x++;
        answer.emplace_back(x);
      }
    }
  }
  if (x < from) return from / 2 - 1;
  return x / 2;
}

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  vl v(n);
  F(i, 0, n) cin >> v[i];
  l sum = accumulate(all(v), l(0));
  vl bottom;
  F(i, 0, sum) {
    l t = i;
    l x = 0;
    F(j, 0, n) {
      x = x << 1;
      x += t % 2;
      t /= 2;
    }
    bottom.emplace_back(x);
  }
  l start = 1; F(i, 0, n) start = start << 1;
  l p = 0;
  B(i, 0, n) {
    l j = v[i];
    while (j and p < sum) {
      cout << start + (bottom[p] >> (n - i - 1)) << lf;
      j--;
      p++;
    }
    start /= 2;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
#else
  solve(cin, cout);
#endif
}
