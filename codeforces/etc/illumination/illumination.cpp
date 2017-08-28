#if defined(LOCAL)
#define PROBLEM_NAME "illumination"
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

struct Edge {
  l to, id, from;
};

struct Graph {
  l v_count, e_count;
  vector<vector<Edge>> adj;
  vector<Edge> edges;

  Graph(l n) {
    v_count = n;
    adj.resize(n);
    e_count = 0;
  }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = e_count; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = e_count; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    e_count++;
    edges.emplace_back(ab);
  }

  void add_directed(l a, l b) {
    Edge ab; ab.id = e_count; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    e_count++;
    edges.emplace_back(ab);
  }
};

struct SCC {
  vl age, lowlink, component;
  l time, count;
  stack<l> path;

  SCC(Graph& g) {
    age.resize(g.v_count);
    lowlink.resize(g.v_count);
    component.resize(g.v_count);
    time = 0;
    count = 0;
    F(i, 0, g.v_count) if (not age[i]) dfs(g, i);
  }

  void dfs(Graph& g, l a) {
    time++;
    age[a] = lowlink[a] = time;
    path.push(a);
    for (auto e : g.adj[a]) {
      l b = e.to;
      if (not age[b]) dfs(g, b);
      lowlink[a] = min(lowlink[a], lowlink[b]);
    }
    if (lowlink[a] == age[a]) {
      while (1) {
        l t = path.top(); path.pop();
        lowlink[t] = INF;
        component[t] = count;
        if (t == a) break;
      }
      count++;
    }
  }
};

// variables [0, n)
struct SAT2 { // requires YY and Y
  Graph g;
  l size;

  SAT2(l n): g(n * 2), size(n) {}

  void add_or(l x, l y) {
    g.add_directed(neg(x), y);
    g.add_directed(neg(y), x);
  }

  void add_true(l x) {
    g.add_directed(neg(x), x);
  }

  void add_xor(l x, l y) {
    add_or(x, y);
    add_or(neg(x), neg(y));
  }

  l neg(l x) { return (x + size) % (2 * size); }

  bool is_solvable() {
    SCC scc(g);
    F(i, 0, size) if (scc.component[i] == scc.component[neg(i)])
      return false;
    return true;
  }
};

void solve(istream& cin, ostream& cout) {
  l n, r, k;
  cin >> n >> r >> k;
  vl xx(k), yy(k);
  F(i, 0, k) cin >> xx[i] >> yy[i];
  SAT2 sat(k);
  F(i, 0, k) F(j, i + 1, k) {
    if (xx[i] == xx[j] and abs(yy[i] - yy[j]) <= 2 * r)
      sat.add_or(i, j);
    if (yy[i] == yy[j] and abs(xx[i] - xx[j]) <= 2 * r)
      sat.add_or(sat.neg(i), sat.neg(j));
  }
  bool answer = sat.is_solvable();
  cout << (answer ? "YES" : "NO") << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
