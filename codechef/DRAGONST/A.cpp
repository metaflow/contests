#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "A"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lll = tuple<l, l, l>; using vlll = vector<lll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<long>::max();
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

struct Graph {
  vvl adj;
  vvl W;
  vvl up;
  vvl wup;
  vl depth;

  Graph(l n) {
    adj.resize(n);
    depth.resize(n);
    W.resize(n);
    l k = 0;
    while ((1 << k) <= n) k++;
    up.resize(k, vl(n, -1));
    wup.resize(k, vl(n));
  }

  void build_up(l a) {
    F(i, 1, up.size()) {
      l p = up[i - 1][a];
      l t = up[i - 1][p];
      if (t == -1) break;
      up[i][a] = t;
      wup[i][a] = max(wup[i - 1][a], wup[i - 1][p]);
    }
  }

  ll walk(l a, l d) {
    l k = 0;
    l w = 0;
    while (d > 0) {
      if (d % 2) {
        w = max(w, wup[k][a]);
        a = up[k][a];
      }
      d /= 2;
      k++;
    }
    return make_pair(a, w);
  }

  ll lca(l a, l b) {
    l w = 0, t;
    tie(a, t) = walk(a, depth[a] - depth[b]);
    w = max(w, t);
    tie(b, t) = walk(b, depth[b] - depth[a]);
    w = max(w, t);
    if (a == b) return make_pair(a, w);
    B(i, 0, up.size()) {
      if (up[i][a] != up[i][b]) {
        w = max(w, wup[i][a]);
        a = up[i][a];
        w = max(w, wup[i][b]);
        b = up[i][b];
      }
    }
    w = max(w, max(wup[0][a], wup[0][b]));
    return make_pair(up[0][a], w);
  }

  void dfs(l a) {
    l m = adj[a].size();
    F(i, 0, m) {
      l b = adj[a][i];
      if (up[0][a] == b) continue;
      depth[b] = depth[a] + 1;
      up[0][b] = a;
      wup[0][b] = W[a][i];
      build_up(b);
      dfs(b);
    }
  }
};

#if defined(RANDOM_TEST)
// TODO add random set size 

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}

void solve_brute(istream& cin, ostream& cout) {
  l tcc, n; cin >> tcc >> n;
  vll pp(n);
  F(i, 0, n) cin >> pp[i].first >> pp[i].second;
  vlll edges; // (min distance, from, to)
  F(i, 0, n) F(j, 0, n) {
    if (i == j) continue;
    edges.emplace_back(abs(pp[i].first - pp[j].first) +
                       abs(pp[i].second - pp[j].second), i, j);
  }
  sort(all(edges));
  disjoint_set S(n);
  Graph g(n);
  for (auto e : edges) {
    l a, b, w; tie(w, a, b) = e;
    if (a < 0 or b < 0) break;
    if (S.connected(a, b)) continue;
    S.connect(a, b);
    g.adj[a].emplace_back(b);
    g.w[a].emplace_back(w);
    g.adj[b].emplace_back(a);
    g.w[b].emplace_back(w);
  }
  l Q; cin >> Q;
  while (Q--) {
    l a, b; cin >> a >> b; a--; b--;
    // cout << a << lf;
  }
  l total_w = 0;
  for (auto ww : g.w) for (auto w : ww) total_w += w;
  cout << total_w / 2 << lf;
}

void generate(l size, ostream& cout) {
  cout << 1 << lf;
  cout << size << lf;
  F(i, 0, size) {
    cout << random_in_range(0, 10) << ' '
         << random_in_range(0, 10) << lf;
  }
  cout << 0 << lf;
}

#endif

struct point {
  l x, y, id, adj, w;
};


void find_closest(vector<point>& pp, l from, l to) {
  if (to - from < 2) return;
  l mid = (from + to) / 2;
  find_closest(pp, from, mid);
  find_closest(pp, mid, to);
  vector<point> ss(to - from);
  l i = from, j = mid;
  l best = -INF, best_id = -1;
  F(k, 0, to - from) {
    if (j >= to or (i < mid and (pp[i].x + pp[i].y) < (pp[j].x + pp[j].y))) {
      l t = (pp[i].x - pp[i].y) - best;
      if (pp[i].w > t) {
        pp[i].adj = best_id;
        pp[i].w = t;
      }
      ss[k] = pp[i];
      i++;
    } else {
      ss[k] = pp[j];
      l c = pp[j].x - pp[j].y;
      if (c > best) {
        best = c;
        best_id = pp[j].id;
      }
      j++;
    }
  }
  F(k, from, to) pp[k] = ss[k - from];
}

void add_edges(vlll& ee, vector<point>& pp) {
  sort(all(pp), [](point const& a, point const& b) {
      if (a.y != b.y) return a.y < b.y;
      return a.x > b.x;
    });
  F(i, 0, pp.size()) {
    pp[i].adj = -1;
    pp[i].w = INF;
  }
  // for (auto p : pp) cerr << '(' << p.x << ", " << p.y << ") ";
  // cerr << lf;
  find_closest(pp, 0, pp.size());
  F(i, 0, pp.size()) {
    if (pp[i].adj != -1) {
      ee.emplace_back(pp[i].w, pp[i].id, pp[i].adj);
    }
  }
}

void solve(istream& cin, ostream& cout) {
  l tcc;
  cin >> tcc;
  while (tcc--) {
    l n; cin >> n;
    vector<point> pp(n);
    F(i, 0, n) {
      cin >> pp[i].x >> pp[i].y;
      pp[i].id = i;
    }
    vlll edges;
    add_edges(edges, pp);
    F(i, 0, n) pp[i].x = -pp[i].x;
    add_edges(edges, pp);
    F(i, 0, n) swap(pp[i].x, pp[i].y);
    add_edges(edges, pp);
    F(i, 0, n) pp[i].x = -pp[i].x;
    add_edges(edges, pp);
    disjoint_set S(n);
    sort(all(edges));
    // L(edges);
    // TODO: no L output for in random tests
    Graph g(n);
    for (auto e : edges) {
      l a, b, w; tie(w, a, b) = e;
      if (a < 0 or b < 0) break;
      if (S.connected(a, b)) continue;
      S.connect(a, b);
      g.adj[a].emplace_back(b);
      g.W[a].emplace_back(w);
      g.adj[b].emplace_back(a);
      g.W[b].emplace_back(w);
    }
    g.depth[0] = 0;
    g.dfs(0);
    l Q; cin >> Q;
    while (Q--) {
      l a, b; cin >> a >> b; a--; b--;
      l w, t;
      tie(t, w) = g.lca(a, b);
      cout << w << lf;
    }
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
