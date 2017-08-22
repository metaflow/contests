#if defined(LOCAL)
#define PROBLEM_NAME "pieceittogether"
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

const l dr[] = {1, 0, -1, 0};
const l dc[] = {0, 1, 0, -1};

// n parameters [0, n)
struct SAT2 {
  Graph g;
  l size;

  SAT2(l n): g(n * 2), size(n) {}

  void add_or(l x, l y) {
    // L("or", x, y);
    g.add_directed(neg(x), y);
    g.add_directed(neg(y), x);
  }

  void add_true(l x) {
    // L("T", x);
    g.add_directed(neg(x), x);
  }

  void add_xor(l x, l y) {
    // L("xor", x, y);
    add_or(x, y);
    add_or(neg(x), neg(y));
  }

  l neg(l x) { return (x + size) % (2 * size); }

  bool is_solvable() {
    SCC scc(g);
    F(i, 0, size) if (scc.component[i] == scc.component[neg(i)])
      return false; // TODO use L(a, b, result) syntax instead
    return true;
  }
};

bool in_bounds(l r, l c, l rows, l cols) {
  return 0 <= r and r < rows and 0 <= c and c < cols;
}

void solve(istream& cin, ostream& cout) {
  l rows, cols;
  cin >> rows >> cols;
  vector<string> grid(rows);
  F(i, 0, rows) cin >> grid[i];
  vector<vvl> term_id(4, vvl(rows, vl(cols, -1)));
  l black_count = 0, white_count = 0;
  l id = 0;
  F(i, 0, rows) F(j, 0, cols) {
    if (grid[i][j] == 'B') {
      black_count++;
      F(d, 0, 4) term_id[d][i][j] = id++;
    }
    if (grid[i][j] == 'W') white_count++;
  }
  SAT2 sat(id);
  bool ok = (black_count * 2 == white_count);
  if (ok) F(i, 0, rows) F(j, 0, cols) {
    if (grid[i][j] == 'W') {
      vl bb;
      F(d, 0, 4) {
        l ni = i + dr[d], nj = j + dc[d];
        if (not in_bounds(ni, nj, rows, cols) or grid[ni][nj] != 'B') continue;
        bb.emplace_back(term_id[(d + 2) % 4][ni][nj]);
      }
      ok = ok and not bb.empty();
      if (not ok) break;
      F(x, 0, bb.size()) F(y, x + 1, bb.size())
        sat.add_or(sat.neg(bb[x]), sat.neg(bb[y]));
    }
    if (grid[i][j] == 'B') {
      F(d, 0, 4) {
        l r = i + dr[d], c = j + dc[d];
        if (not in_bounds(r, c, rows, cols) or grid[r][c] != 'W')
          sat.add_true(term_id[(d + 2) % 4][i][j]);
      }
      sat.add_xor(term_id[0][i][j], term_id[2][i][j]);
      sat.add_xor(term_id[1][i][j], term_id[3][i][j]);
    }
  }
  ok = (ok) and (sat.is_solvable());
  cout << (ok ? "YES" : "NO") << lf;
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
