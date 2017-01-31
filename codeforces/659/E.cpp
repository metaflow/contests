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
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

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
    vb visited(n);
    vector<unordered_set<l>> adj(n);
    for (l i = 0; i < m; i++) {
      l a, b; cin >> a >> b; a--; b--;
      adj[a].emplace(b);
      adj[b].emplace(a);
    }
    l orphans = 0;
    for (l i = 0; i < n; i++) {
      if (visited[i]) continue;
      l j = i;
      while (adj[j].size() == 1) {
        visited[j] = true;
        l next = *(adj[j].begin());
        adj[next].erase(j);
        j = next;
      }
      if (adj[j].empty()) {
        visited[j] = true;
        orphans++;
      }
    }
    cout << orphans << '\n';
  }
}
