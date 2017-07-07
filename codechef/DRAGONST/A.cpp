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

void find_edges(l xfrom, l xto, vll& p, vlll& edges) {
  if (xto <= xfrom) return;
  l xmid = (xfrom + xto) / 2;
  l start = lower_bound(all(p), make_pair(xfrom, -INF)) - p.begin();
  l mid = upper_bound(all(p), make_pair(xmid, +INF)) - p.begin();
  l finish = upper_bound(all(p), make_pair(xto, +INF)) - p.begin();
  L(start, mid, finish, p);
  if (mid - start > 0 and finish - mid > 0) {
    L("non empty");
    vll L, R;
    F(i, start, mid) L.emplace_back(p[i].second, i);
    F(i, mid, finish) R.emplace_back(p[i].second, i);
    sort(all(L));
    sort(all(R));
    {
      // y asc
      l best_sum = INF;
      l best_i = -1;
      l k = 0;
      F(i, 0, L.size()) {
        l z = p[L[i].second].second - p[L[i].second].first;
        while (k < R.size() and R[k].first <= L[i].first) {
          l t = p[R[k].second].first - p[R[k].second].second;
          if (t < best_sum) {
            best_sum = t;
            best_i = R[k].second;
          }
          k++;
        }
        if (best_sum + z < get<0>(edges[i])) {
          get<0>(edges[i]) = best_sum + z;
          get<2>(edges[i]) = best_i;
        }
      }
    }
    {
      // y desc
      l best_sum = INF;
      l best_i = -1;
      l k = R.size() - 1;
      B(i, 0, L.size()) {
        l z = p[L[i].second].second + p[L[i].second].first;
        while (k >= 0 and R[k].first >= L[i].first) {
          l t = p[R[k].second].first + p[R[k].second].second;
          if (t < best_sum) {
            best_sum = t;
            best_i = R[k].second;
          }
          k--;
        }
        if (best_sum + z < get<0>(edges[i])) {
          get<0>(edges[i]) = best_sum + z;
          get<2>(edges[i]) = best_i;
        }
      }
    }
  }
  find_edges(xfrom, xmid, p, edges);
  find_edges(xmid + 1, xto, p, edges);
}

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
  vvl up;
  vl depth;
  vvl w;

  Graph(l n) {
    adj.resize(n);
    depth.resize(n);
    w.resize(n);
    l k = 0;
    while ((1 << k) <= n) k++;
    up.resize(k, vl(n, -1));
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
};

void solve(istream& cin, ostream& cout) {
  l tcc;
  cin >> tcc;
  while (tcc--) {
    l n; cin >> n;
    // Graph g(n);
    vll pp(n);
    F(i, 0, n) cin >> pp[i].first >> pp[i].second;
    sort(all(pp));
    vlll edges(n, make_tuple(INF, 0, -1)); // (min distance, from, to)
    F(i, 0, n) get<1>(edges[i]) = i;
    find_edges(pp[0].first, pp[n - 1].first, pp, edges);
    F(i, 1, n) {
      if (pp[i].first == pp[i - 1].first) {
        edges.emplace_back(pp[i].second - pp[i - 1].second, i, i - 1);
      }
    }
    disjoint_set S(n);
    sort(all(edges));
    Graph g(n);
    for (auto e : edges) {
      l a, b, w; tie(w, a, b) = e;
      if (a < 0 or b < 0) break;
      if (S.connected(a, b)) continue;
      L(a, b, w, "connected");
      S.connect(a, b);
      g.adj[a].emplace_back(b);
      g.w[a].emplace_back(w);
      g.adj[b].emplace_back(a);
      g.w[b].emplace_back(b);
    }
    l Q; cin >> Q;
    while (Q--) {
      l a, b; cin >> a >> b; a--; b--;
      cout << a << lf;
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
