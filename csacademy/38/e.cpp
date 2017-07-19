#if defined(LOCAL)
#define PROBLEM_NAME "e"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

#if defined(LOCAL)
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#endif

struct Graph {
  vvl adj;
  vvl up;
  vl depth;
  vl value;
  vl parent;

  Graph(l n) {
    adj.resize(n);
    value.resize(n);
    parent.resize(n);
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

  void dfs(l root) {
    for (auto a : adj[root]) {
      if (a == parent[root]) continue;
      parent[a] = root;
      value[a] = 1 - value[root];
      dfs(a);
    }
  }
};

void solve(istream& cin, ostream& cout) {
  l tcc;
  cin >> tcc;
  while (tcc--) {
    l n; cin >> n;
    Graph g(n);
    F(i, 0, n - 1) {
      l a, b; cin >> a >> b; a--; b--;
      g.adj[a].emplace_back(b);
      g.adj[b].emplace_back(a);
    }
    g.value[0] = 0;
    g.parent[0] = -1;
    g.dfs(0);
    vl black, white;
    F(i, 0, n) {
      if (g.value[i]) {
        white.emplace_back(i);
      } else {
        black.emplace_back(i);
      }
    }
    l b = -1, w = -1;
    for (auto i : black) {
      if (g.adj[i].size() != 1) continue;
      if (white[0] != g.adj[i].back()) {
        b = i;
        w = white[0];
        break;
      }
      if (white.back() != g.adj[i].back()) {
        b = i;
        w = white.back();
        break;
      }
    }
    for (auto i : white) {
      if (g.adj[i].size() != 1) continue;
      if (black[0] != g.adj[i].back()) {
        w = i;
        b = black[0];
        break;
      }
      if (black.back() != g.adj[i].back()) {
        w = i;
        b = black.back();
        break;
      }
    }
    if (w == -1) {
      cout << -1 << lf;
    } else {
      vl answer;
      for (auto i : white) if (i != w) answer.emplace_back(i);
      answer.emplace_back(w);
      answer.emplace_back(b);
      for (auto i : black) if (i != b) answer.emplace_back(i);
      F(i, 0, answer.size()) {
        if (i) cout << ' ';
        cout << answer[i] + 1;
      }
      cout << lf;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
#else
  solve(cin, cout);
#endif
}
