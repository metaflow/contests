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
  l n, k;
  while (cin >> n >> k) {
    unordered_map<l, vl> m;
    vl q(n);
    l sum = 0, a = 0, b = 0;
    m[0].emplace_back(-1);
    F(i, 0, n) {
      cin >> q[i];
      sum += q[i];
      m[sum].emplace_back(i);
      a = max(a, sum);
      b = min(b, sum);
    }
    sum = 0;
    l answer = 0;
    vl v;
    v.emplace_back(1);
    if (k == 1) {
    } else if (k == -1) {
      v.emplace_back(-1);
    } else {
      l x = k;
      while (abs(x) <= (a - b)) {
        v.emplace_back(x);
        x *= k;
      }
    }
    F(i, 0, n) {
      sum += q[i];
      for (const l x : v) {
        l y = sum - x;
        if (m.count(y)) answer += lower_bound(ALL(m[y]), i) - m[y].begin();
      }
    }
    cout << answer << '\n';
  }
}
