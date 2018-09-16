#if defined(LOCAL)
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#endif
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <math.h>
#include <limits>
#include <numeric>
#include <queue>

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
const double EPS = 1e-10; static constexpr auto PI = 3.1415926;
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

const l MOD = e9 + 7; // end of template

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
  l good;

  Graph(l n): v(n), e(0), good(0) {
    adj.resize(v);
  }

  l add_node() { adj.resize(++v); return v - 1; }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = e; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = e; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    e++;
  }
};

void solve(istream& in, ostream& out) {
  l n, m, k; in >> n >> m >> k;
  Graph g(n);
  vll edges(m);
  vl c(n);
  F(i, 0, m) {
    l a, b; in >> a >> b; a--; b--;
    g.add_undirected(a, b);
    edges[i].first = a; edges[i].second = b;
    c[a]++; c[b]++;
  }
  l z = n;
  vb visited(g.v);
  {
    queue<l> q;
    F(i, 0, n) {
      if (c[i] >= k) continue;
      q.emplace(i);
      visited[i] = true;
      z--;
    }
    while (not q.empty()) {
      l a = q.front(); q.pop();
      for (auto e : g.adj[a]) {
        if (visited[e.to]) continue;
        c[e.to]--;
        if (c[e.to] < k) {
          q.emplace(e.to);
          visited[e.to] = true;
          z--;
        }
      }
    }
  }
  vl answer(m);
  B(i, 0, m) {
    answer[i] = z;
    l x, b; tie(x, b) = edges[i];
    queue<l> q;
    if (visited[x] || visited[b]) continue;
    c[x]--;
    if (c[x] < k) {
      q.emplace(x);
      visited[x] = true;
      z--;
    }
    c[b]--;
    if (c[b] < k) {
      q.emplace(b);
      visited[b] = true;
      z--;
    }
    while (not q.empty()) {
      l a = q.front(); q.pop();
      for (auto e : g.adj[a]) {
        if (visited[e.to] || e.id >= i) continue;
        c[e.to]--;
        if (c[e.to] < k) {
          q.emplace(e.to);
          visited[e.to] = true;
          z--;
        }
      }
    }
  }
  F(i, 0, m) out << answer[i] << lf;
}

int main(int argc, char **argv) {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  tst::test_init(argc, argv);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  tst::maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
