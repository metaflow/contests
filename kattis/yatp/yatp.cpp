#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "yatp"
const double _max_double_error = 1e-9;
#include "testutils.h"
// #include "testlib.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  l id, value, best;
  bool visited;
  vector<pedge> adjusted;
  l subtreeSize = 1; bool blocked;
  pnode parent;
};

struct edge {
  pnode from, to;
  l value;
};

void connect(pnode &a, pnode &b, l value) {
  pedge ea = make_shared<edge>();
  ea->from = a; ea->to = b; ea->value = value;
  a->adjusted.emplace_back(ea);
}

// add bool blocked and subtreeSize to node
void dfsSubtreeSize(pnode u) {u->subtreeSize = 1;
  for (auto e : u->adjusted) {
    auto v = e->to;
    if (v->blocked or u->parent == v) continue;
    v->parent = u;
    dfsSubtreeSize(v);
    u->subtreeSize += v->subtreeSize;
  }
}

struct Line {
  l a, b;
  pnode at;
  Line(l _a, l _b, pnode _at): a(_a), b(_b), at(_at) {}
  bool operator < (const Line& rhs) {
    return tie(a, b) < tie(rhs.a, rhs.b);
  }

  l value(Line rhs) {
    return a * rhs.a + b + rhs.b;
  }
};

void dfs(pnode u, l d, vector<Line>& parts) {
  parts.emplace_back(u->value, d, u);
  for (auto e : u->adjusted) {
    auto v = e->to;
    if (v->blocked or v == u->parent) continue;
    v->parent = u;
    dfs(v, d + e->value, parts);
  }
}

void solveFor(pnode u, l size) {
  u->parent = nullptr;
  vector<Line> parts; // (a, b), a * x + b
  dfs(u, 0, parts);
  sort(all(parts));
  vector<Line> hull;
  for (auto p : parts) {
    if (hull.empty()) {
      hull.emplace_back(p); continue;
    }
    if (hull.back().a == p.a) continue;
    while (hull.size() > 1) {
      // p -> r -> t
      Line r = hull[hull.size() - 1];
      Line t = hull[hull.size() - 2];
      if ((t.b - p.b) * (r.a - t.a) < (t.b - r.b) * (p.a - t.a)) break;
      hull.pop_back();
    }
    hull.emplace_back(p);
  }
  l i = hull.size() - 1;
  for (auto p : parts) {
    while (i > 0 and p.value(hull[i]) > p.value(hull[i - 1])) i--;
    p.at->best = min(p.at->best, p.value(hull[i]));
  }
}

void decompose(pnode u) {
  u->parent = nullptr;
  dfsSubtreeSize(u);
  l total = u->subtreeSize;
  queue<pnode> q;
  q.emplace(u);
  l best = total;
  pnode centroid = u;
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    l t = total - v->subtreeSize;
    for (auto e : v->adjusted) {
      if (e->to->blocked or e->to == v->parent) continue;
      t = max(t, e->to->subtreeSize);
      q.emplace(e->to);
    }
    if (t < best) {
      centroid = v;
      best = t;
    }
  }
  solveFor(centroid, best);
  centroid->blocked = true;
  for (auto e : centroid->adjusted) {
    if (not e->to->blocked) decompose(e->to);
  }
}

void solve(istream& cin, ostream& cout) {
  l N; cin >> N;
  graph g(N);
  F(i, 0, N) {
    g[i] = make_shared<node>();
    g[i]->id = i + 1;
    cin >> g[i]->value;
    g[i]->best = g[i]->value * g[i]->value;
  }
  F(i, 0, N - 1) {
    l a, b, w; cin >> a >> b >> w; a--; b--;
    connect(g[a], g[b], w);
    connect(g[b], g[a], w);
  }
  decompose(g[0]);
  l sum = 0;
  for (auto u : g) sum += u->best;
  cout << sum << lf;
}

#if defined(RANDOM_TEST)

void solve_brute(istream& cin, ostream& cout) {
  l N; cin >> N;
  graph g(N);
  F(i, 0, N) {
    g[i] = make_shared<node>();
    g[i]->id = i + 1;
    cin >> g[i]->value;
    g[i]->best = g[i]->value * g[i]->value;
  }
  F(i, 0, N - 1) {
    l a, b, w; cin >> a >> b >> w; a--; b--;
    connect(g[a], g[b], w);
    connect(g[b], g[a], w);
  }
  F(i, 0, N) {
    g[i]->parent = nullptr;
    queue<pair<pnode, l>> q;
    q.emplace(g[i], 0);
    while (not q.empty()) {
      auto p = q.front(); q.pop();
      auto u = p.first;
      auto d = p.second;
      g[i]->best = min(g[i]->best, d + g[i]->value * u->value);
      for (auto e : u->adjusted) {
        auto v = e->to;
        if (v == u->parent) continue;
        v->parent = u;
        q.emplace(v, d + e->value);
      }
    }
  }
  l sum = 0;
  for (auto u : g) sum += u->best;
  cout << sum << lf;
}

void generate(long long size, ostream& cout) {
  cout << size << lf;
  F(i, 0, size) {
    if (i) cout << ' ';
    cout << rnd.next(1, 100);
  }
  cout << lf;
  auto edges = rnd.tree(size);
  for (auto e : edges) {
    cout << e.first + 1 << ' ' << e.second + 1 << ' '
         << rnd.next(0, 100) << lf;
  }
}

#endif

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _random_test_count = 100;
  maybe_run_tests(cin, cout);
#else
  solve_brute(cin, cout);
#endif
}
