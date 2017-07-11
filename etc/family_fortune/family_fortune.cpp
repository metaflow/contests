#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "family_fortune"
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
  vl value;
  vl id_to_pos;
  vl jump;
  vl path;
  l counter;

  Graph(l n) {
    adj.resize(n);
    depth.resize(n);
    l k = 0;
    while ((1 << k) <= n) k++;
    up.resize(k, vl(n, -1));
    value.resize(n);
    id_to_pos.resize(n);
    jump.resize(n);
    path.resize(n);
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

  void dfs(l a) {
    l p = counter;
    path[p] = a;
    counter++;
    for (auto b : adj[a]) dfs(b);
    jump[p] = counter;
  }
};

void solve(istream& cin, ostream& cout) {
  l n, k;
  while (cin >> n >> k, n) {
    Graph g(n);
    l root = - 1;
    F(i, 0, n) {
      l p, w; cin >> p >> w; p--;
      g.value[i] = w;
      if (p > -1) {
        g.adj[p].emplace_back(i);
      } else {
        root = i;
      }
    }
    g.dfs(root);
    vl row(n + 1);
    F(i, 0, k) {
      vl next(n + 1, -INF);
      F(j, 0, n) {
        row[j + 1] = max(row[j + 1], row[j]);
        next[g.jump[j]] = max(next[g.jump[j]], row[j] + g.value[g.path[j]]);
      }
      swap(next, row);
    }
    l answer = 0;
    F(i, 0, n + 1) answer = max(answer, row[i]);
    cout << answer << lf;
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
