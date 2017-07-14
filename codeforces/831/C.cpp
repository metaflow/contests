#if defined(LOCAL)
// #define RANDOM_TEST
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

l MAX = 4 * e6 + 1;
void solve(istream& cin, ostream& cout) {
  l n, k;
  while (cin >> n >> k) {
    vl d(n);
    F(i, 0, n) cin >> d[i];
    l x;
    unordered_set<l> b;
    F(i, 0, k) {
      cin >> x;
      b.emplace(x);
    }
    unordered_set<l> starts;
    l offset = 0;
    F(i, 0, n) {
      if (i) offset -= d[i];
      auto left = b;
      l first = x + offset;
      left.erase(first);
      l t = first;
      F(j, 1, n) {
        t += d[j];
        left.erase(t);
      }
      if (left.empty()) {
        starts.emplace(first - d[0]);
      }
    }
    cout << starts.size() << lf;
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
