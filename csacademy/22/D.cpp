#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
#define ALL(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

l number_of_divisors(l n) {
  l r = 0;
  F(i, 1, n) if (n % i == 0) r++;
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s;
  while (cin >> s) {
    vl v(s.size());
    vl q(s.size());
    l n = s.size();
    F(i, 0, n) {
      q[i] = -1;
      if (s[i] == '0') q[i] = 0;
      if (s[i] == '1') q[i] = 1;
    }
    F(w, 1, n + 1) {
      if (n % w != 0) continue;
      bool ok = true;
      F(k, 0, w) {
        v[k] = -1;
        for (l i = k; i < n; i += w) {
          if (q[i] == -1) continue;
          if (v[k] == -1) {
            v[k] = q[i];
          }
          if (v[k] != q[i]) {
            ok = false;
            break;
          }
        }
        if (not ok) break;
      }
      if (not ok) continue;
      F(k, 0, w) for (l i = k; i < n; i += w) {
        q[i] = (v[k] == 1) ? 1 : 0;
      }
    }
    for (l i : q) cout << i;
    cout << '\n';
  }
}
