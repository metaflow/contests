#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "D"
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
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

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

bool bipartite_matching_connect(const l u, vvl& m, vl& to, vb& used, l bound) {
  for (size_t v = 0; v < to.size(); v++) {
    if ((m[u][v] > bound) || used[v]) continue;
    used[v] = true;
    if (to[v] == -1 || bipartite_matching_connect(to[v], m, to, used, bound)) {
      to[v] = u;
      return true;
    }
  }
  return false; // return to; to get actual connections
}

// {A} => {B}, m[i][j] if A[i] -> B[j]
l bipartite_matching(vvl& m, l bound) {
  if (m.empty()) return 0;
  vl to(m[0].size(), -1);
  int result = 0;
  for (size_t u = 0; u < m.size(); u++) {
    vb used(to.size());
    if (bipartite_matching_connect(u, m, to, used, bound)) {
      result++;
    } else return 0;
  }
  return result;
}

void solve(istream& cin, ostream& cout) {
  l n, k, door;
  while (cin >> n >> k >> door) {
    vl xx(n); F(i, 0, n) cin >> xx[i];
    vl yy(k); F(i, 0, k) cin >> yy[i];
    vb taken(k);
    vvl d(n, vl(k));
    l upper = 0;
    l lower = 0;
    F(i, 0, n) {
      l t = INF;
      F(j, 0, k) {
        d[i][j] = abs(xx[i] - yy[j]) + abs(yy[j] - door);
        upper = max(upper, d[i][j]);
        t = min(t, d[i][j]);
      }
      lower = max(lower, t);
    }
    l answer = binary_search_lower(lower, upper, [&](l const bound) {
      return bipartite_matching(d, bound) == n;
    });
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
