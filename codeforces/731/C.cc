#include<bits/stdc++.h>
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

#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream& s) { s << endl; } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

struct node {
  l color;
  vl adjusted;
  bool visited = false;
};

l non_majority_size(l u, vector<node>& g, const l k) {
  vl colors;
  l total = 0;
  g[u].visited = true;
  queue<l> q;
  q.emplace(u);
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    total++;
    colors.emplace_back(g[v].color);
    LOG << "c " << colors[g[v].color] << " " << g[v].color;
    for (auto t : g[v].adjusted) {
      if (g[t].visited) continue;
      g[t].visited = true;
      q.emplace(t);
    }
  }
  l majority = 0;
  sort(colors.begin(), colors.end());
  l x = -1;
  l count = 0;
  for (auto c : colors) {
    if (c == x) {
      count++;
    } else {
      majority = max(majority, count);
      count = 1;
      x = c;
    }
  }
  majority = max(majority, count);
  LOG << total << " - " << majority;
  return total - majority;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m, k;
  while (cin >> n >> m >> k) {
    LOG << "--------";
    LOG << n << " " << m << " " << k;
    vector<node> g(n);
    for (l i = 0; i < n; i++) cin >> g[i].color;
    for (l i = 0; i < m; i++) {
      l a, b; cin >> a >> b; a--; b--;
      g[a].adjusted.emplace_back(b);
      g[b].adjusted.emplace_back(a);
    }
    l answer = 0;
    for (l i = 0; i < n; i++) {
      if (g[i].visited) continue;
      answer += non_majority_size(i, g, k);
    }
    cout << answer << endl;
  }
}
