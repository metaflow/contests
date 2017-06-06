#if defined(LOCAL)
#define PROBLEM_NAME "C"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

l f(vl& v, l a, l b, l K) { // [a, b)
  if (a >= b) return 0;
  if (b - a == 1) return (v[a] >= K) ? 1 : 0;
  l m = a + (b - a) / 2;
  vl left, right;
  l t = 0, j = 0;
  l r = f(v, a, m, K) + f(v, m, b, K);
  B(i, m - 1, a - 1) {
    t += v[i];
    j++;
    left.emplace_back(K * j - t);
  }
  t = 0; j = 0;
  F(i, m, b) {
    j++;
    t += v[i];
    right.emplace_back(t - K * j);
  }
  sort(all(right));
  for (auto i : left) {
    auto p = lower_bound(all(right), i);
    r += distance(p, right.end());
  }
  return r;
}

void solve(istream& cin, ostream& cout) {
  l N, K;
  while (cin >> N >> K) {
    vl v(N); F(i, 0, N) cin >> v[i];
    l answer = f(v, 0, N, K);
    cout << answer << lf;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
