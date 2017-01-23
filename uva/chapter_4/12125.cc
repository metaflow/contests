#include<bits/stdc++.h>
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


// v max flow
struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  int age;
  l x, y;
  vector<pedge> adjusted;
  pedge back;
};

struct edge {
  pnode from, to;
  int flow, initial_flow;
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
  ea->from = a; ea->to = b; ea->initial_flow = w; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->initial_flow = 0; eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

int max_flow(vector<pnode> &g, pnode &source, pnode &sink) {
  int result = 0;
  for (auto& u : g)
    for (auto& e : u->adjusted)
      e->flow = e->initial_flow;
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
}
// ^ max flow

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  for (l tc = 1; tc <= tcc; tc++) {
    l n; double d; cin >> n >> d;
    l dd = ceil(d * d);
    graph in(n), out(n), g;
    pnode source = make_shared<node>();
    g.emplace_back(source);
    for (l i = 0; i < n; i++) {
      in[i] = make_shared<node>();
      out[i] = make_shared<node>();
      g.emplace_back(in[i]);
      g.emplace_back(out[i]);
    }
    l total = 0;
    for (l i = 0; i < n; i++) {
      cin >> in[i]->x >> in[i]->y;
      l j, k; cin >> j >> k;
      total += j;
      connect(source, in[i], j);
      connect(in[i], out[i], k);
    }
    for (l i = 0; i < n; i++) {
      for (l j = 0; j < n; j++) {
        if (i == j) continue;
        l dx = in[i]->x - in[j]->x;
        l dy = in[i]->y - in[j]->y;
        if (dx * dx + dy * dy > dd) continue;
        connect(out[i], in[j], total);
      }
    }
    vl answers;
    for (l i = 0; i < n; i++) {
      if (max_flow(g, source, in[i]) == total) {
        answers.emplace_back(i);
      }
    }
    if (answers.empty()) {
      cout << "-1" << endl;
    } else {
      bool first = true;
      for (auto i : answers) {
        if (!first) cout << " ";
        first = false;
        cout << i;
      }
      cout << endl;
    }
  }
}
