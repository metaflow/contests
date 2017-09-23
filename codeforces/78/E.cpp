#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})


// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr
/*
// v max flow
struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
int age;
vector<pedge> adjusted;
pedge back;
};

struct edge {
pnode from, to;
int flow;
pedge opposite;
};

int adjust(pedge e, int d) {
if (!e) return d;
d = adjust(e->from->back, min(d, e->flow));
e->flow -= d;
e->opposite->flow += d;
return d;
}

void connect(pnode &a, pnode &b, int w) {
pedge ea = make_shared<edge>();
pedge eb = make_shared<edge>();
ea->from = a; ea->to = b; ea->flow = w; ea->opposite = eb;
eb->from = b; eb->to = a; eb->flow = 0; eb->opposite = ea;
a->adjusted.emplace_back(ea);
b->adjusted.emplace_back(eb);
}

int max_flow(vector<pnode> &g, pnode &source, pnode &sink) {
int result = 0;
while (true) {
for (auto u : g) u->age = 0;
queue<pnode> q;
q.push(source); source->age = 1;
while (!(q.empty() || sink->age != 0)) {
auto u = q.front(); q.pop();
for (auto e : u->adjusted) {
auto v = e->to;
if (v->age != 0 || e->flow == 0) continue;
v->back = e;
v->age = u->age + 1;
q.push(v);
}
}
if (sink->age == 0) break;
for (auto e : sink->adjusted) {
auto o = e->opposite;
if (o->from->age != sink->age - 1 || o->flow == 0) continue;
result += adjust(o, o->flow);
}
}
return result;
} // ^ max flow
*/


struct Edge {
  l to;
  l id, from;
  l opposite; // for flow, index in 'to'
  l capacity; // for flow
  l cost;
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

  void add_flow(l a, l b, l w, l cost) {
    Edge ab; ab.id = e; ab.from = a; ab.to = b; ab.capacity = w; ab.cost = cost;
    ab.opposite = adj[b].size();
    Edge ba; ba.id = e; ba.from = b; ba.to = a; ba.capacity = 0; ba.cost = 0;
    e++;
    ba.opposite = adj[a].size();
    adj[a].emplace_back(ab);
    adj[b].emplace_back(ba);
  }
};

struct MaxFlow {
  l result_flow;
  vl age;
  vl back;
  vvl capacity;

  MaxFlow(Graph& g, l source, l sink) {
    result_flow = 0;
    age.resize(g.v);
    back.resize(g.v);
    capacity.resize(g.v);
    F(i, 0, g.v) {
      capacity[i].resize(g.adj[i].size());
      F(j, 0, g.adj[i].size()) capacity[i][j] = g.adj[i][j].capacity;
    }
    while (true) {
      fill(all(age), 0);
      fill(all(back), -1);
      queue<l> q;
      q.push(source); age[source] = 1;
      while (not (q.empty() || age[sink])) {
        l u = q.front(); q.pop();
        F(j, 0, g.adj[u].size()) {
          auto& e = g.adj[u][j];
          l v = e.to;
          if (age[v] || capacity[u][j] == 0) continue;
          back[v] = e.opposite;
          age[v] = age[u] + 1;
          q.push(v);
        }
      }
      if (age[sink] == 0) break; // unreachable
      for (auto& e : g.adj[sink]) {
        l u = e.to;
        if (age[u] != age[sink] - 1 or capacity[u][e.opposite] == 0) continue;
        vll path;
        path.emplace_back(u, e.opposite);
        while (back[u] != -1) {
          auto& uv = g.adj[u][back[u]];
          u = uv.to;
          path.emplace_back(u, uv.opposite);
        }
        // adjust path
        l d = INF;
        for (auto p : path) d = min(d, capacity[p.first][p.second]);
        for (auto p : path) {
          capacity[p.first][p.second] -= d;
          auto& t = g.adj[p.first][p.second];
          capacity[t.to][t.opposite] += d;
        }
        result_flow += d;
      }
    }
  }
};

l n;

l linear(l t, l r, l c) {
  return t * n * n + r * n + c;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l T;
  while (cin >> n >> T) {
    vector<string> lab(n);
    Graph g((T + 1) * n * n + 2);
    auto source = linear(T, n-1, n-1) + 1;
    auto sink = linear(T, n-1, n-1) + 2;
    vector<ll> z;
    for (l r = 0; r < n; r++) {
      cin >> lab[r];
      for (l c = 0; c < n; c++) {
        if (lab[r][c] == 'Y') continue;
        if (lab[r][c] == 'Z') {
          z.emplace_back(r, c);
          continue;
        }
        g.add_flow(source, linear(0, r, c), lab[r][c] - '0', 0);
        lab[r][c] = '0';
      }
    }
    for (l r = 0; r < n; r++) {
      string row; cin >> row;
      for (l c = 0; c < n; c++) {
        if (row[c] == 'Y' or row[c] == 'Z') continue;
        g.add_flow(linear(T, r, c), sink, row[c] - '0', 0);
      }
    }
    const l dr[] = {1, 0, -1, 0};
    const l dc[] = {0, 1, 0, -1};
    for (l t = 0; t < T; t++) {
      // connect corridors
      for (l r = 0; r < n; r++) {
        for (l c = 0; c < n; c++) {
          g.add_flow(linear(t, r, c), linear(t + 1, r, c), INF, 0);
          if (lab[r][c] != '0') continue;
          for (l d = 0; d < 4; d++) {
            l r_ = r + dr[d];
            l c_ = c + dc[d];
            if (r_ < 0 or r_ >= n or c_ < 0 or c_ >= n or lab[r_][c_] != '0')
              continue;
            g.add_flow(linear(t, r, c), linear(t + 1, r_, c_), INF, 0);
          }
        }
      }
      // spread
      vll z_;
      for (auto e : z) {
        l r, c; tie(r, c) = e;
        for (l d = 0; d < 4; d++) {
          l r_ = r + dr[d];
          l c_ = c + dc[d];
          if (r_ < 0 or r_ >= n or c_ < 0 or c_ >= n or lab[r_][c_] != '0')
            continue;
          z_.emplace_back(r_, c_);
          lab[r_][c_] = 'Z';
        }
      }
      swap(z_, z);
    }
    MaxFlow mf(g, source, sink);
    cout << mf.result_flow << '\n';
  }
}
