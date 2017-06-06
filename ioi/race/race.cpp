#if defined(LOCAL)
#define PROBLEM_NAME "race"
const double _max_double_error = 1e-9;
#include "testutils.h"
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
l N, K;

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  l id, value;
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

const l MAXK = e6 + 1;
l answer;

void dfs(pnode u, l sum, l depth, vll& paths) {
  if (sum > K or depth >= answer) return;
  paths.emplace_back(sum, depth);
  for (auto e : u->adjusted) {
    auto v = e->to;
    if (v->blocked or v == u->parent) continue;
    v->parent = u;
    dfs(v, sum + e->value, depth + 1, paths);
  }
}

void solveFor(pnode root, l size) {
  root->parent = nullptr;
  mll distance;
  distance[0] = 0;
  for (auto e : root->adjusted) {
    auto v = e->to;
    if (v->blocked) continue;
    v->parent = root;
    vll paths;
    dfs(v, e->value, 1, paths);
    for (auto p : paths) {
      if (distance.count(K - p.first))
        answer = min(answer, distance[K - p.first] + p.second);
    }
    for (auto p : paths) {
      if (distance.count(p.first) == 0 or distance[p.first] > p.second) {
        distance[p.first] = p.second;
      }
    }
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
  while (cin >> N >> K) {
    graph g(N);
    F(i, 0, N) {
      g[i] = make_shared<node>();
      g[i]->id = i + 1;
    }
    F(i, 0, N-1) {
      l a, b, w; cin >> a >> b >> w;
      connect(g[a], g[b], w);
      connect(g[b], g[a], w);
    }
    answer = INF;
    decompose(g[0]);
    if (answer == INF) answer = -1;
    cout << answer << lf;
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
