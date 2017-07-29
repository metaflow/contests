#if defined(LOCAL)
#define PROBLEM_NAME "C"
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

struct disjoint_set { // set of [0..n-1]
  vl parent;
  l components_count_;

  disjoint_set(size_t n) {
    components_count_ = n;
    parent.resize(n);
    for (size_t i = 0; i < n; i++) parent[i] = i;
  }
  l get_parent(l i) {
    if (parent[i] != i) parent[i] = get_parent(parent[i]);
    return parent[i];
  }
  bool connected(l i, l j) { return get_parent(i) == get_parent(j); }
  void connect(l i, l j) {
    i = get_parent(i);
    j = get_parent(j);
    if (i != j) {
      parent[i] = j;
      components_count_--;
    }
  }
  l components_count() { return components_count_; }
};


struct point { l x, y, id; };
struct edge { l a, b, d; };

l distance(const point a, const point b) {
  return abs(a.x - b.x) + abs(a.y - b.y);
}

void add_edges(vector<point>& p, vector<edge>& edges) {
  // sort(all(p), [](const point& a, const point& b) { return a.y < b.y; });
  l best = 0;
  l n = p.size();
  F(i, 1, n) if (p[i].x - p[i].y < p[best].x - p[best].y) best = i;
  F(i, 0, n) {
    if (i != best) {
      edge e;
      e.d = distance(p[i], p[best]);
      e.a = i;
      e.b = best;
      edges.emplace_back(e);
    }
  }
  F(i, 0, n) swap(p[i].x, p[i].y), p[i].x = -p[i].x;
}

void solve(istream& cin, ostream& cout) {
  l tcc; cin >> tcc;
  while (tcc--) {
    l n; cin >> n;
    vector<point> p(n);
    F(i, 0, n) {
      p[i].id = i;
      cin >> p[i].x >> p[i].y;
    }
    vector<edge> edges;
    add_edges(p, edges);
    add_edges(p, edges);
    add_edges(p, edges);
    add_edges(p, edges);
    sort(all(edges), [](const edge& a, const edge& b) { return a.d > b.d; });
    disjoint_set s(n);
    l answer = INF;
    for (auto e : edges) {
      answer = e.d;
      s.connect(e.a, e.b);
      if (s.components_count() == 1) break;
    }
    cout << answer << lf;
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
