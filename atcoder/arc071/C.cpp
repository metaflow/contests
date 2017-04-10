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
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string s1, s2;
  while (cin >> s1 >> s2) {
    vl acc1(s1.size() + 1);
    F(i, 0, s1.size()) acc1[i + 1] = acc1[i] + (s1[i] == 'A' ? 2 : 1);
    vl acc2(s2.size() + 1);
    F(i, 0, s2.size()) acc2[i + 1] = acc2[i] + (s2[i] == 'A' ? 2 : 1);
    l q; cin >> q;
    while (q--) {
      l a, b, c, d; cin >> a >> b >> c >> d;
      if ((acc1[b] - acc1[a - 1]) % 3 == (acc2[d] - acc2[c - 1]) % 3) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }
  }
}
