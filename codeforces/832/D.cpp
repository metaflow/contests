#if defined(LOCAL)
#define PROBLEM_NAME "D"
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

  Graph(l n) {
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

  void dfs(l root) {
    for (auto a : adj[root]) {
      if (up[0][root] == a) continue;
      up[0][a] = root;
      depth[a] = depth[root] + 1;
      build_up(a);
      dfs(a);
    }
  }

  l calc(l a, l b, l c) {
    // a->b and c->b
    l ab = lca(a, b);
    l ac = lca(a, c);
    l bc = lca(b, c);
    if (depth[ab] < depth[bc]) return depth[b] - depth[bc] + 1;
    if (depth[ab] < depth[ac]) return depth[b] + depth[ac] - 2 * depth[ab] + 1;
    return depth[b] - depth[ab] + 1;
  }
};

void solve(istream& cin, ostream& cout) {
  l N, Q;
  while (cin >> N >> Q) {
    Graph g(N);
    F(i, 1, N) {
      l a; cin >> a; a--;
      g.adj[a].emplace_back(i);
      g.adj[i].emplace_back(a);
    }
    g.dfs(0);
    F(i, 0, Q) {
      l a, b, c; cin >> a >> b >> c; a--; b--; c--;
      l answer = g.calc(a, b, c);
      answer = max(answer, g.calc(a, c, b));
      answer = max(answer, g.calc(b, c, a));
      answer = max(answer, g.calc(b, a, c));
      answer = max(answer, g.calc(c, a, b));
      answer = max(answer, g.calc(c, b, a));
      cout << answer << lf;
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
