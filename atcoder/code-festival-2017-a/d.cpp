#if defined(LOCAL)
#define PROBLEM_NAME "d"
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
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

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
struct SAT2 { // requires 'graph' and 'scc'
  Graph g;
  l size;

  SAT2(l n): g(n * 2), size(n) {}

  // x => y
  void add(l x, l y) { g.add_directed(x, y); }

  void add_or(l x, l y) {
    add(neg(x), y);
    add(neg(y), x);
  }

  void add_true(l x) { add(neg(x), x); }

  void add_false(l x) { add(x, neg(x)); }

  void add_xor(l x, l y) {
    add_or(x, y);
    add_or(neg(x), neg(y));
  }

  void add_not_and(l x, l y) {
    add_or(neg(x), neg(y));
  }

  // x <=> y
  void add_eq(l x, l y) {
    add_or(neg(x), y);
    add_or(x, neg(y));
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

void solve(istream& cin, ostream& cout) {
  l n, m, k; cin >> n >> m >> k;
  SAT2 sat(n * m * 6);
  // 1. pick one and only one
  F(i, 0, n) {
    F(j, 0, m) {
      l sh = (i * m + j) * 6;
      // no more than one
      F(a, 0, 4) {
        F(b, 0, 4) {
          if (a != b) sat.add(sh + a, sat.neg(sh + b));
        }
      }
      sat.add(sat.neg(sh), sh + 4);
      sat.add(sat.neg(sh + 1), sh + 4);
      sat.add(sat.neg(sh + 2), sh + 5);
      sat.add(sat.neg(sh + 3), sh + 5);
      sat.add_xor(sh + 4, sh + 5);
    }
  }
  // 2. distance restrictions
  F(i, 0, n) {
    F(j, 0, m) {
      F(x, i-k, i+k + 1) {
        l y = j - k + abs(x - j);
        if (x >= 0 and x < n and y >= 0 and y < m) {
          F(c, 0, 4) sat.add_not_and((i * m + j) * 6 + c, (x * m + y) * 6 + c);
        }
        l y = j + k - abs(x - j);
        if (x >= 0 and x < n and y >= 0 and y < m) {
          F(c, 0, 4) sat.add_not_and((i * m + j) * 6 + c, (x * m + y) * 6 + c);
        }
      }
    }
  }
  auto answer = sat.solve();
  L(answer);
  string color = "RGBY";
  F(i, 0, n) {
    F(j, 0, m) {
      F(c, 0, 4) {
        if (answer[(i * m + j) * 6 + c]) cout << color[c];
      }
    }
    cout << lf;
  }
}

// return false to stop
bool generate_random(l tc, ostream& cout) {
  l max_cases = 10000;
  if (tc % (max_cases / 100) == 0) cerr << (tc * 100 / max_cases) << "%\r";
  cout << (tc % 10 + 1) << ' ' << ((tc / 10) % 10 + 1) << ' ' << ((tc / 100) % 10 + 1) << lf;
  cerr << (tc % 10 + 1) << ' ' << ((tc / 10) % 10 + 1) << ' ' << ((tc / 100) % 10 + 1) << endl;
  return tc < max_cases;
}

bool solution_checker(istream& input, istream& /* expected */,
                      istream& actual, ostream& out) {
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
