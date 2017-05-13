#include <bits/stdc++.h>
#if defined(LOCAL)
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

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string a, b;
  while (cin >> a >> b) {
    sort(all(a));
    sort(all(b), greater<char>());
    l n = a.size();
    l f = 0, t = n - 1;
    a.resize((n + 1) / 2);
    b.resize(n / 2);
    l pa = 0, pb = 0;
    vector<char> answer(n);
    F(i, 0, n) {
      auto x = a[pa];
      auto y = b[pb];
      if (i % 2) {
        if (x >= y) {
          answer[t] = b.back();
          b.pop_back();
          t--;
        } else {
          answer[f] = b[pb];
          pb++;
          f++;
        }
      } else {
        if (y <= x) {
          answer[t] = a.back();
          a.pop_back();
          t--;
        } else {
          answer[f] = a[pa];
          pa++;
          f++;
        }
      }
    }
    for (auto c : answer) cout << c;
    cout  << lf;
  }
}
