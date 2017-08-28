#if defined(LOCAL)
#define PROBLEM_NAME "c_beaming_with_joy"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x...) (x)
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

l val(l i) {
  return i;
}

// variables [0, n)
struct SAT2 { // requires 'graph' and 'scc'
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

  // returns vector [-1, ...] if there is no solution, or [0, 1,..] assigments
  vl solve() {
    SCC scc(g);
    vvl v(scc.count);
    F(i, 0, scc.component.size()) {
      v[scc.component[i]].emplace_back(i);
    }
    vl solution(size, -1);
    F(i, 0, size) if (scc.component[i] == scc.component[neg(i)])
      return solution;
    F(i, 0, v.size()) {
      bool take = true;
      for (auto a : v[i]) {
        l t = a; if (t >= size) t = neg(t);
        take = take and solution[t] == -1;
      }
      if (not take) continue;
      for (auto a : v[i]) {
        l t = a; if (t >= size) t = neg(t);
        solution[t] = (t == a ? 1 : 0);
      }
    }
    return solution;
  }
};

struct Ray { l r, c, dr, dc, condition; };

void solve(istream& cin, ostream& cout) {
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    l n, m; cin >> n >> m;
    vector<string> grid(n);
    F(i, 0, n) cin >> grid[i];
    vll beams;
    F(i, 0, n) F(j, 0, m) {
      if (grid[i][j] == '|') grid[i][j] = '-';
      if (grid[i][j] == '-') beams.emplace_back(i, j);
    }
    SAT2 sat(beams.size());
    vector<vvl> passing(n, vvl(m, vl(2, -1)));
    F(i, 0, beams.size()) {
      l _i = sat.neg(i);
      auto p = beams[i];
      queue<Ray> q;
      // try -
      Ray a;
      a.r = p.first; a.c = p.second - 1; a.dr = 0; a.dc = -1; a.condition = i;
      q.emplace(a);
      a.r = p.first; a.c = p.second + 1; a.dr = 0; a.dc = +1; a.condition = i;
      q.emplace(a);
      // try |
      a.r = p.first + 1; a.c = p.second; a.dr = +1; a.dc = 0; a.condition = _i;
      q.emplace(a);
      a.r = p.first - 1; a.c = p.second; a.dr = -1; a.dc = 0; a.condition = _i;
      q.emplace(a);
      vll pos, neg;
      bool pos_ok = true, neg_ok = true;
      while (not q.empty()) {
        auto ray = q.front(); q.pop();
        // out of grid
        if (ray.r < 0 or ray.r >= n or ray.c < 0 or ray.c >= m) continue;
        auto c = grid[ray.r][ray.c];
        // wall
        if (c == '#') continue;
        // beam
        if (c == '-') {
          if (ray.condition == i) {pos_ok = false;} else {neg_ok = false;}
          continue;
        }
        // empty space
        if (c == '.') {
          if (ray.condition == i) {
            pos.emplace_back(ray.r, ray.c);
          } else {
            neg.emplace_back(ray.r, ray.c);
          }
        }
        // mirror /
        if (c == '/') {
          swap(ray.dr, ray.dc);
          ray.dr = -ray.dr;
          ray.dc = -ray.dc;
        }
        // mirror '\'
        if (c == '\\') {
          swap(ray.dr, ray.dc);
        }
        ray.r += ray.dr;
        ray.c += ray.dc;
        q.emplace(ray);
      }
      if (pos_ok) {
        for (auto t : pos) {
          swap(passing[t.first][t.second][0], passing[t.first][t.second][1]);
          passing[t.first][t.second][0] = i;
        }
      } else {
        sat.add_true(_i);
      }
      if (neg_ok) {
        for (auto t : neg) {
          swap(passing[t.first][t.second][0], passing[t.first][t.second][1]);
          passing[t.first][t.second][0] = _i;
        }
      } else {
        sat.add_true(i);
      }
    }
    bool ok = true;
    F(i, 0, n) F(j, 0, m) if (grid[i][j] == '.') {
      if (passing[i][j][0] == -1) {
        ok = false;
        break;
      }
      if (passing[i][j][1] == -1) {
        sat.add_true(passing[i][j][0]);
        continue;
      }
      sat.add_or(passing[i][j][0], passing[i][j][1]);
    }
    auto solution = sat.solve();
    if (solution.size()) {
      ok = ok and solution[0] != -1;
      F(i, 0, beams.size()) {
        if (solution[i] == 0) {
          auto p = beams[i];
          grid[p.first][p.second] = '|';
        }
      }
    }
    cout << "Case #" << ("tc", val(tc)) << ": ";
    if (ok) {
      cout << "POSSIBLE" << lf;
      for (auto s : grid) cout << s << lf;
    } else {
      cout << "IMPOSSIBLE" << lf;
    }
  }
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
