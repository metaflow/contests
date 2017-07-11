#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "knapsack"
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
  vl values;
  vl path;
  vl jump;
  l counter;

  Graph(l n) {
    adj.resize(n);
    depth.resize(n);
    l k = 0;
    while ((1 << k) <= n) k++;
    up.resize(k, vl(n, -1));
    values.resize(n);
    path.resize(n);
    jump.resize(n);
    counter = 0;
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

  void dfs(l root) {
    l t = counter;
    counter++;
    path[t] = root;
    for (auto b : adj[root]) dfs(b);
    jump[t] = counter;
  }
};

void solve(istream& cin, ostream& cout) {
  l n, m;
  cin >> n >> m;
  Graph g(n + 1);
  F(i, 0, n) {
    l a, w; cin >> a >> w;
    g.adj[a].emplace_back(i + 1);
    g.values[i + 1] = w;
  }
  g.dfs(0);
  vvb pp(n + 2, vb(m + 1));
  B(i, 0, n + 1) {
    pp[i] = pp[g.jump[i]];
    l v = g.values[g.path[i]];
    pp[i][v] = true;
    F(j, 1, m - v + 1) pp[i][j + v] = pp[i][j + v] | pp[i + 1][j];
  }
  l answer = 0;
  B(i, 1, m + 1) if (pp[0][i]) {
    answer = i;
    break;
  }
  cout << answer << lf;
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
