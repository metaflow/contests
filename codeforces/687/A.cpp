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
  l n, m;
  while (cin >> n >> m) {
    vl color(n);
    vvl adjusted(n);
    F(i, 0, m) {
      l a, b; cin >> a >> b; a--; b--;
      adjusted[a].emplace_back(b);
      adjusted[b].emplace_back(a);
    }
    bool ok = true;
    F(i, 0, n) {
      if (color[i]) continue;
      queue<l> q;
      q.emplace(i);
      color[i] = 1;
      while (not q.empty()) {
        l j = q.front(); q.pop();
        for (auto k : adjusted[j]) {
          if (color[k]) {
            ok = ok and (color[k] == -color[j]);
          } else {
            color[k] = -color[j];
            q.emplace(k);
          }
        }
      }
    }
    if (ok) {
      l a = 0;
      for (l i : color) if (i == 1) a++;
      cout << a << '\n';
      bool first = true;
      F(i, 0, n) {
        if (color[i] != 1) continue;
        if (not first) cout << ' ';
        first = false;
        cout << (i + 1);
      }
      cout << '\n';
      a = 0;
      for (l i : color) if (i == -1) a++;
      cout << a << '\n';
      first = true;
      F(i, 0, n) {
        if (color[i] != -1) continue;
        if (not first) cout << ' ';
        first = false;
        cout << (i + 1);
      }
      cout << '\n';
    } else {
      cout << "-1\n";
    }
  }
}
