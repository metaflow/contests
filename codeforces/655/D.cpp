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
const char LF = '\n';
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
    vvll in(n); // (to, #)
    vvl out(n);
    vl unvisited_in(n);
    vl value(n);
    F(i, 0, m) {
      l a, b; cin >> a >> b; a--; b--;
      out[a].emplace_back(b);
      in[b].emplace_back(a, i + 1);
      unvisited_in[b]++;
    }
    queue<l> q;
    F(i, 0, n) if (unvisited_in[i] == 0) q.emplace(i);
    l max_edge = 0, max_v = -1;
    while (not q.empty()) {
      l a = q.front(); q.pop();
      l e = 0;
      for (auto p : in[a]) {
        if (value[a] < value[p.first] + 1) {
          value[a] = value[p.first] + 1;
          e = p.second;
        }
      }
      max_edge = max(max_edge, e);
      max_v = value[a];
      for (auto b : out[a]) {
        unvisited_in[b]--;
        if (unvisited_in[b] == 0) q.emplace(b);
      }
    }
    if (max_v != n - 1) {
      cout << "-1\n";
    } else {
      cout << max_edge << LF;
    }
  }
}
