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
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    l n, m, q;
    cin >> n >> m >> q;
    vl seats(n);
    vl cust(m);
    F(i, 0, q) {
      l x, y; cin >> x >> y; x--; y--;
      seats[x]++;
      cust[y]++;
    }
    l r = 0;
    for (auto i : cust) r = max(r, i);
    l sum = 0;
    F(i, 0, n) {
      sum += seats[i];
      r = max(r, (sum + i) / (i + 1));
    }
    l p = 0;
    for (l i : seats) p += max((l)0, i - r);
    cout << "Case #" << tc << ": " << r << ' ' << p << lf;
  }
}
