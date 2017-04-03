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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l a, b, c, d;
  F(a, 0, 2) F(b, 0, 2) F(c, 0, 2) F(d, 0, 2) {
    l e = a | b;
    l f = c ^ d;
    l g = b & c;
    l h = a | d;
    l k = e & f;
    l m = g ^ h;
    l n = k | m;
    cout << a << b << c << d << ' ' << n << endl;
  }
  return 0;
  while (cin >> a >> b >> c >> d) {
    // a = 1 - a;
    // b = 1 - b;
    // c = 1 - c;
    // d = 1 - d;
    l e = a | b;
    l f = c ^ d;
    l g = b & c;
    l h = a | d;
    l k = e & f;
    l m = g ^ h;
    l n = k | m;
    cout << h << '\n';
  }
}
