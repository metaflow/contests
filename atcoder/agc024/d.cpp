#if defined(LOCAL)
#define PROBLEM_NAME "d"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
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
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

struct Edge {
  l to;
  l from;
  l id;
  // l opposite; // for flow, index in 'to'
  // l capacity; // for flow
  // l cost;
};

struct Graph {
  l v, e; // number of vertices and edges
  vector<vector<Edge>> adj;

  Graph(l n): v(n), e(0) {
    adj.resize(v);
  }

  l add_node() { adj.resize(++v); return v - 1; }

  void add_simple(l a, l b) { // for tree-like
    Edge ab; ab.to = b;
    adj[a].emplace_back(ab);
    e++;
  }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = e; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = e; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    e++;
  }

  void add_directed(l a, l b) {
    Edge ab; ab.id = e; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    e++;
  }

  //  void add_flow(l a, l b, l w, l cost) {
  // Edge ab; ab.id = e; ab.from = a; ab.to = b; ab.capacity = w; ab.cost = cost;
  // ab.opposite = adj[b].size();
  // Edge ba; ba.id = e; ba.from = b; ba.to = a; ba.capacity = 0; ba.cost = 0;
  // e++;
  // ba.opposite = adj[a].size();
  // adj[a].emplace_back(ab);
  // adj[b].emplace_back(ba);
  // }
};



void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  Graph g(n);
  F(i, 0, n - 1) {
    l a, b; cin >> a >> b; a--; b--;
    g.add_undirected(a, b);
  }
  l x = 0;
  // TODO: update bfs snippet
  {
    vl age(g.v);
    queue<l> q;
    q.emplace(0);
    age[0] = 1;
    while (not q.empty()) {
      l a = q.front(); q.pop();
      for (auto e : g.adj[a]) {
        if (age[e.to]) continue;
        age[e.to] = age[a] + 1;
        q.emplace(e.to);
        x = e.to;
      }
    }
  }
  l y = x;
  vl path;
  {
    vl age(g.v);
    queue<l> q;
    q.emplace(x);
    age[x] = 1;
    while (not q.empty()) {
      l a = q.front(); q.pop();
      for (auto e : g.adj[a]) {
        if (age[e.to]) continue;
        age[e.to] = age[a] + 1;
        q.emplace(e.to);
        y = e.to;
      }
    }
    path.emplace_back(y);
    B(i, 1, age[y]) {
      for (auto e : g.adj[path.back()]) {
        if (age[e.to] == i) {
          path.emplace_back(e.to);
          break;
        }
      }
    }
  }
  l d = path.size();
  l colors = (d + 1) / 2;
  L(x, y, d, colors, path);
  // TODO: special case for n == 2
  vl splits(colors + 1);
  l t = 1;
  {
    vl age(g.v);
    queue<l> q;
    q.emplace(path[d / 2]);
    age[path[d / 2]] = 1;
    if (d % 2 == 0) {
      q.emplace(path[d / 2 - 1]);
      age[path[d / 2 - 1]] = 1;
    }
    while (not q.empty()) {
      l a = q.front(); q.pop();
      l s = 0;
      for (auto e : g.adj[a]) {
        if (age[e.to]) continue;
        s++;
        age[e.to] = age[a] + 1;
        q.emplace(e.to);
      }
      splits[age[a]] = max(splits[age[a]], s);
    }
  }
  F(i, 1, colors) t *= splits[i];
  L(splits);
  if (d % 2 == 0) t *= 2;
  cout << colors << ' ' << t << lf;
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
