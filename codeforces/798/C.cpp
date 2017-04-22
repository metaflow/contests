// #define ONLINE_JUDGE
#include <bits/stdc++.h>
#if !defined(ONLINE_JUDGE)
#include "prettyprint.h"
#endif

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

l gcd(l a, l b) {
  while (b) { l t = b; b = a % b; a = t; }
  return a;
}

l lcm(l a, l b) { return a * b / gcd(a, b); }


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vl v(n);
    l g = 0;
    l answer = 0;
    bool prev_odd = false;
    F(i, 0, n) {
      cin >> v[i];
      if (v[i] % 2) {
        if (prev_odd) {
          prev_odd = false;
          answer++;
        } else {
          prev_odd = true;
        }
      } else {
        if (prev_odd) answer += 2;
        prev_odd = false;
      }
      g = gcd(g, v[i]);
    }
    if (prev_odd) answer += 2;
    if (g > 1) answer = 0;
    cout << "YES" << lf << answer << lf;
  }
}
