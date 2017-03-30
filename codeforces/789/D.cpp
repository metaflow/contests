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
  l n, m;
  while (cin >> n >> m) {
    vvl adj(n);
    vb with_loops(n);
    l loops = 0;
    l start = 0;
    F(i, 0, m) {
      l a, b; cin >> a >> b; a--; b--;
      if (a == b) {
        loops++;
        with_loops[a] = true;
        continue;
      }
      start = a;
      adj[a].emplace_back(b);
      adj[b].emplace_back(a);
    }
    // connected? (free nodes are ok)
    vb visited(n);
    queue<l> q;
    q.emplace(start);
    visited[start] = true;
    l touched = 0;
    while (not q.empty()) {
      l u = q.front(); q.pop();
      touched += adj[u].size();
      for (auto v : adj[u]) {
        if (not visited[v]) {
          visited[v] = true;
          q.emplace(v);
        }
      }
    }
    bool ok = true;
    F(i, 0, n) ok = ok and ((not with_loops[i]) or visited[i]);
    if ((not ok) or (touched != 2 * (m - loops)) or ((m - loops) == 0)) {
      cout << 0 << '\n';
      continue;
    }

    l answer = (m - loops) * loops * 2 + loops * (loops - 1);
    F(i, 0, n) {
      l x = adj[i].size();
      answer += x * (x - 1);
    }
    cout << answer / 2 << '\n';
  }
}
