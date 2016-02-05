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
  int age, penalty;
  vector<pedge> adjusted;
  pedge back;
};

struct edge {
  pnode from, to;
  l flow, original_flow;
  pedge opposite;
};

int adjust(pedge e, l d) {
  if (!e) return d;
  if (e->flow) d = min(d, e->flow);
  // cerr << " + " << d << " ";
  d = adjust(e->from->back, d);
  if (e->flow) e->flow -= d;
  e->opposite->flow += d;
  return d;
}

void connect(pnode &a, pnode &b, int w) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->flow = w; ea->original_flow = w; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->flow = 0; eb->original_flow = 0; eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

int max_flow(vector<pnode> &g, pnode &source, pnode &sink, l added) {
  int result = 0;
  l p = 0;
  while (true) {
    for (auto u : g) u->age = u->penalty = 0;
    queue<pnode> q;
    sink->back.reset();
    q.push(source); source->age = 1;
    while (!(q.empty() || sink->back)) {
      auto u = q.front(); q.pop();
      for (auto e : u->adjusted) {
        auto v = e->to;
        l x = u->penalty;
        if (e->flow == 0 && e->original_flow == 0) continue;
        if (e->flow == 0) x++;
        if (x > p) continue;
        if (v->age != 0 && x >= v->penalty) continue;
        v->back = e;
        v->age = u->age + 1;
        v->penalty = x;
        q.push(v);
      }
    }
    if (!sink->back) {
      p++;
      if (result == 0) break; // disconnected
      continue;
    }
    l a = INF;
    if (p) a = added / p;
    // cerr << p << " " << a << endl;
    a = adjust(sink->back, a);
    // cerr << a << endl;
    if (a == 0) break;
    added -= a * p;
    result += a;
  }
  return result;
}
// ^ max flow

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, k;
  while (cin >> n >> k) {
    graph g(n);
    for (auto &u : g) u = make_shared<node>();
    for (l i = 0; i < n; i++) {
      for (l j = 0; j < n; j++) {
        l w; cin >> w;
        if (w == 0) continue;
        connect(g[i], g[j], w);
      }
    }
    l m = max_flow(g, g[0], g[n - 1], k);
    cout << m << endl;
  }
}
