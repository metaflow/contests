#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "E"
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

bool on_border(l x, l y, l R, l C) {
  return (x == 0) or (x == R) or (y == 0) or (y == C);
}

l position(l x, l y, l R, l C) {
  if (y == 0) return x;
  if (x == R) return y + R;
  if (y == C) return 2 * R - x + C;
  return 2 * R + 2 * C - y;
}

void solve(istream& cin, ostream& cout) {
  l R, C, N;
  while (cin >> R >> C >> N) {
    vll border;
    F(i, 0, N) {
      l x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
      if (on_border(x1, y1, R, C) and on_border(x2, y2, R, C)) {
        l from = position(x1, y1, R, C);
        l to = position(x2, y2, R, C);
        border.emplace_back(from, i);
        border.emplace_back(to, i);
      }
    }
    sort(all(border));
    stack<l> s;
    for (auto b : border) {
      if (not s.empty() and s.top() == b.second) {
        s.pop();
      } else {
        s.push(b.second);
      }
    }
    cout << (s.empty() ? "YES" : "NO") << lf;
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
