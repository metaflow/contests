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

const l MAX = 35;

void solve(istream& cin, ostream& cout) {
  l n;
  while (cin >> n) {
    vl v(n);
    l z = 0;
    F(i, 0, n) {
      cin >> v[i];
      z = z | v[i];
    }
    if (z == 0) {
      cout << 1 << lf;
      continue;
    }
    l i = 0, j = 0;
    vl frq(MAX);
    l answer = INF;
    l m = 0;
    while (j < n) {
      while (j < n and m != z) {
        F(k, 0, MAX) if ((v[j] >> k) & (l)1) {
          if (frq[k] == 0) m = m + ((l)1 << k);
          frq[k]++;
        }
        j++;
      }
      while (i < j and m == z) {
        answer = min(answer, j - i);
        F(k, 0, MAX) if ((v[i] >> k) & (l)1) {
          frq[k]--;
          if (frq[k] == 0) m = m - ((l)1 << k);
        }
        i++;
      }
    }
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
