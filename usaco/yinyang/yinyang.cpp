#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
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
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool visited;
  l subtreeSize = 1; bool blocked;
  vector<pedge> adjusted;
  pnode parent;
  l id;
};

struct edge {
  pnode from, to;
  pedge opposite;
  l w;
};

void connect(pnode &a, pnode &b, int w) {
  pedge ea = make_shared<edge>();
  ea->from = a; ea->to = b; ea->w = w;
  a->adjusted.emplace_back(ea);
}

void dfsSubtreeSize(pnode u) {
  u->subtreeSize = 1;
  for (auto e : u->adjusted) {
    auto v = e->to;
    if (v->blocked or u->parent == v) continue;
    v->parent = u;
    dfsSubtreeSize(v);
    u->subtreeSize += v->subtreeSize;
  }
}

void dfs(pnode u, l value, vl& with, vl& without, vl& seen, l offset) {
  if (seen[value + offset]) {
    with[value + offset]++;
  } else {
    without[value + offset]++;
  }
  seen[value + offset]++;
  for (auto e : u->adjusted) {
    auto v = e->to;
    if (v == u->parent or v->blocked) continue;
    v->parent = u;
    dfs(v, value + e->w, with, without, seen, offset);
  }
  seen[value + offset]--;
}

l solveFor(pnode u, l n) {
  vl withTotal(n * 2 + 1), withoutTotal(n * 2 + 1);
  // LOG << "solve " << u->id << endl;
  l result = 0;
  for (auto e : u->adjusted) {
    auto v = e->to;
    if (v->blocked) continue;
    v->parent = u;
    vl with(n * 2 + 1), without(n * 2 + 1), seen(n * 2 + 1);
    dfs(v, e->w, with, without, seen, n);
    // LOG << v->id << " w " << with << " wo " << without << endl;
    F(i, 0, 2 * n + 1) {
      result += with[i] * (withTotal[2 * n - i] + withoutTotal[2 * n - i]);
      result += without[i] * withTotal[2 * n - i];
    }
    result += without[n] * withoutTotal[n];
    F(i, 0, 2 * n + 1) {
      withTotal[i] += with[i];
      withoutTotal[i] += without[i];
    }
  }
  result += withTotal[n];
  // LOG << result << endl;
  return result;
}

l decompose(pnode u) {
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
  l answer = solveFor(centroid, best);
  centroid->blocked = true;
  for (auto e : centroid->adjusted) {
    if (not e->to->blocked) answer += decompose(e->to);
  }
  return answer;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ifstream fin("yinyang.in"); cin.rdbuf(fin.rdbuf());
  ofstream fout("yinyang.out"); cout.rdbuf(fout.rdbuf());
  // solution
  l n;
  while (cin >> n) {
    graph g(n);
    F(i, 0, n) {
      g[i] = make_shared<node>();
      g[i]->id = i + 1;
    }
    F(i, 0, n - 1) {
      l a, b, w; cin >> a >> b >> w; a--; b--; w = 2 * w - 1;
      connect(g[a], g[b], w);
      connect(g[b], g[a], w);
    }
    l answer = decompose(g[0]);
    cout << answer << lf;
  }
}
