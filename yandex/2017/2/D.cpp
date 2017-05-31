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

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator () (const std::pair<T1,T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);
    return h1 ^ h2;
  }
};


void increment(unordered_map<ll, l, pair_hash>& v, l x, l y) {
  v[make_pair(x, y)]++;
  if (v[make_pair(x, y)] == 5) {
    v.erase(make_pair(x, y));
    increment(v, x + 1, y);
    increment(v, x - 1, y);
    increment(v, x, y + 1);
    increment(v, x, y - 1);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // solution
  l n;
  while (cin >> n) {
    unordered_map<ll, l, pair_hash> v;
    F(i, 0, n) {
      l x, y;
      cin >> x >> y;
      increment(v, x, y);
      cout << v.size() << lf;
    }
  }
}
