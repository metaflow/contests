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
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <memory>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using ii = pair<int, int>;
using lu = unsigned long long;
using l = long long;
using vs = vector<string>;
using vii = vector<ii>;
using vl = vector<l>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using ll = pair<l, l>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using mll = unordered_map<l, l>;
using sl = unordered_set<l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const l e0 = 1, e3 = 1000, e5 = 100000, e6 = 10 * e5, e7 = 10 * e6,
        e8 = 10 * e7, e9 = 10 * e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a, b, c) for (l a = l(b); a < l(c); a++)
#define B(a, b, c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

void solve(istream &in, ostream &out);
int main(int argc, char **argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
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

  Graph(l n) : v(n), e(0) { adj.resize(v); }

  l add_node() {
    adj.resize(++v);
    return v - 1;
  }

  void add_simple(l a, l b) { // for tree-like
    Edge ab;
    ab.to = b;
    adj[a].emplace_back(ab);
    e++;
  }

  void add_undirected(l a, l b) {
    Edge ab;
    ab.id = e;
    ab.from = a;
    ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba;
    ba.id = e;
    ba.from = b;
    ba.to = a;
    adj[b].emplace_back(ba);
    e++;
  }

  void add_directed(l a, l b) {
    Edge ab;
    ab.id = e;
    ab.from = a;
    ab.to = b;
    adj[a].emplace_back(ab);
    e++;
  }

  //  void add_flow(l a, l b, l w, l cost) {
  // Edge ab; ab.id = e; ab.from = a; ab.to = b; ab.capacity = w; ab.cost =
  // cost; ab.opposite = adj[b].size(); Edge ba; ba.id = e; ba.from = b; ba.to =
  // a; ba.capacity = 0; ba.cost = 0; e++; ba.opposite = adj[a].size();
  // adj[a].emplace_back(ab);
  // adj[b].emplace_back(ba);
  // }
};
l ask(vl &idx, l a, l b, l c, l d, istream &in, ostream &out) {
  l k = b - a + d - c;
  if (k <= 0)
    return 0;
  out << "? " << (b - a + d - c) << endl;
  bool s = false;
  F(i, a, b) {
    if (s)
      out << ' ';
    s = true;
    out << idx[i];
  }
  F(i, c, d) {
    if (s)
      out << ' ';
    s = true;
    out << idx[i];
  }
  out << endl;
  l x;
  in >> x;
  if (x < 0) exit(0);
  return x;
}
void solve(istream &in, ostream &out) {
  l n;
  in >> n;
  Graph g(n);
  l d = 0;
  vl idx(n);
  iota(all(idx), 1);
  l p = -1;
  F(i, 1, n) {
    while (d == 0) {
      p++;
      d = ask(idx, p, p + 1, i, n, in, out) - ask(idx, 0, 0, i, n, in, out);
    }
    l a = i;
    l count = n - i;
    while (count > 1) {
      l step = count / 2;
      if (ask(idx, p, p + 1, a, a + step, in, out) -
          ask(idx, 0, 0, a, a + step, in, out) > 0) {
        count = step;
      } else {
        a += step;
        count -= step;
      }
    }
    swap(idx[i], idx[a]);
    g.add_undirected(p, i);
    L(idx[p], idx[i]);
    d--;
  }
  // TODO: use age as snippet bfs.
  vl age(g.v);
  queue<l> q;
  q.emplace(0);
  age[0] = 1;
  while (not q.empty()) {
    l a = q.front();
    q.pop();
    for (auto e : g.adj[a]) {
      if (age[e.to])
        continue;
      age[e.to] = age[a] + 1;
      q.emplace(e.to);
    }
  }
  vl white, black;
  F(i, 0, n) {
    if (age[i] % 2)
      black.emplace_back(idx[i]);
    else
      white.emplace_back(idx[i]);
  }
  l b = ask(black, 0, 0, 0, black.size(), in, out);
  l w = ask(white, 0, 0, 0, white.size(), in, out);
  if (b + w == 0) {
    out << "Y " << black.size() << endl;
    F(i, 0, black.size()) {
      if (i)
        out << ' ';
      out << black[i];
    }
    out << endl;
    return;
  }
  if (w) {
    swap(b, w);
    swap(black, white);
  }
  l count = black.size();
  while (count > 2) {
    l x = count / 3;
    l y = 2 * x;
    if (ask(black, 0, 0, 0, y, in, out)) {
      // A, B
      count = y;
      continue;
    }
    if (ask(black, 0, x, y, count, in, out)) {
      // A, C
      F(i, y, count) {
        black[x + i - y] = black[i];
      }
      count -= x;
      continue;
    }
    // B, C
    F(i, x, count) {
      black[i - x] = black[i];
    }
    count -= x;
  }
  C(count == 2);
  vl bi(n + 1);
  F(i, 0, n) bi[idx[i]] = i;
  vl path1, path2;
  l u = bi[black[0]], v = bi[black[1]];
  while (u != v) {
    if (age[u] < age[v]) {
      swap(u, v);
      swap(path1, path2);
    }
    path1.emplace_back(u);
    for (auto e : g.adj[u]) {
      if (age[e.to] < age[u]) {
        u = e.to;
        break;
      }
    }
  }
  path1.emplace_back(u);
  reverse(all(path2));
  out << "N " << path1.size() + path2.size() << endl;
  bool s = false;
  for (auto i : path1) {
    if (s) out << ' ';
    out << idx[i];
    s = true;
  }
  for (auto i : path2) {
    if (s) out << ' ';
    out << idx[i];
    s = true;
  }
  out << endl;
}
