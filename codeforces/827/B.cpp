#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "B"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

struct Graph {
  vvl adj;
  vvl up;
  vl depth;
  l size;

  Graph(l n) {
    size = n;
    adj.resize(n);
    depth.resize(n);
    l k = 0;
    while ((1 << k) <= n) k++;
    up.resize(k, vl(n, -1));
  }

  void build_up(l a) {
    F(i, 1, up.size()) {
      l t = up[i - 1][up[i - 1][a]];
      if (t == -1) break;
      up[i][a] = t;
    }
  }

  l walk(l a, l d) {
    l k = 0;
    while (d > 0) {
      if (d % 2) a = up[k][a];
      d /= 2;
      k++;
    }
    return a;
  }

  l lca(l a, l b) {
    a = walk(a, depth[a] - depth[b]);
    b = walk(b, depth[b] - depth[a]);
    if (a == b) return a;
    B(i, 0, up.size()) {
      if (up[i][a] != up[i][b]) {
        a = up[i][a];
        b = up[i][b];
      }
    }
    return up[0][a];
  }

  l diameter() {
    queue<l> q;
    q.emplace(0);
    vb visited(size);
    visited[0] = true;
    l x = 0;
    while (not q.empty()) {
      x = q.front(); q.pop();
      for (auto a : adj[x]) {
        if (visited[a]) continue;
        visited[a] = true;
        q.emplace(a);
      }
    }
    visited.clear();
    visited.resize(size);
    vl d(adj.size());
    d[x] = 0;
    visited[x] = true;
    q.emplace(x);
    l result = 0;
    while (not q.empty()) {
      l a = q.front(); q.pop();
      for (l b : adj[a]) {
        if (visited[b]) continue;
        d[b] = result = d[a] + 1;
        visited[b] = true;
        q.emplace(b);
      }
    }
    return result;
  }

  void connect(l a, l b) {
    adj[a].emplace_back(b);
    adj[b].emplace_back(a);
  }
};

#if defined(RANDOM_TEST)

int _random_test_size_from = 0;
int _random_test_size_to = 50;
int _random_test_count = 1;
void solve_brute(istream& cin, ostream& cout) {
  l n, k; cin >> n >> k;
  L(n, k);
  vl parent(n);
  l answer = INF;
  while (parent.back() < n - 1) {
    Graph g(n);
    F(i, 1, n) g.connect(parent[i], i);
    l leafs = 0;
    F(i, 0, n) if (g.adj[i].size() == 1) leafs++;
    if (leafs == k) {
      answer = min(answer, g.diameter());
    }
    l j = 0;
    parent[j]++;
    while (j + 1 < n and parent[j] >= j) {
      parent[j] = 0;
      j++;
      parent[j]++;
    }
  }
  cout << answer << lf;
}

void generate(l size, ostream& cout) {
  l n = 3, k = 2;
  F(i, 0, size) {
    k++;
    if (k == n) {
      n++; k = 2;
    }
  }
  cout << n << ' ' << k << lf;
}

#endif

void solve(istream& cin, ostream& cout) {
  l n, k;
  while (cin >> n >> k) {
    l m = n - k;
    // L(n, k);
    Graph g(n);
    if (k >= m) {
      F(i, 1, m) g.connect(0, i);
      F(i, 0, k) g.connect(i % m, i + m);
    } else {
      F(i, 1, m) g.connect(max(l(0), i - k), i);
      F(i, 0, k) g.connect(max(l(0), i + m - k), i + m);
    }
    cout << g.diameter() << lf;
    F(i, 0, n) {
      for (auto b : g.adj[i]) if (b > i) cout << i + 1 << ' ' << b + 1 << lf;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
