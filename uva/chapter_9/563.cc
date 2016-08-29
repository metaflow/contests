#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;


// v max flow
struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;

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
}
// ^ max flow



const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll s, a, b; cin >> s >> a >> b;
    vector<pnode> g(2 * s * a + 2);
    for (ll i = 0; i < g.size(); i++) g[i] = make_shared<node>();
    pnode sink = g[2 * s * a + 1];
    pnode source = g[2 * s * a];
    for (ll x = 0; x < s; x++) {
      for (ll y = 0; y < a; y++) {
        ll in = (x * a + y) * 2;
        ll out = in + 1;
        connect(g[in], g[out], 1);
        for (ll k = 0; k < 4; k++) {
          int x1 = x + dx[k];
          int y1 = y + dy[k];
          if (x1 < 0 || x1 >= s || y1 < 0 || y1 >= a) continue;
          int c = (x1 * a + y1) * 2;
          // connect(g[c + 1], g[in], 1);
          connect(g[out], g[c], 1);
        }
        if (x == 0 || x == s - 1 || y == 0 || y == a - 1) {
          connect(g[out], sink, 1);
        }
      }
    }
    for (ll i = 0; i < b; i++) {
      ll x, y; cin >> x >> y;
      x--; y--;
      ll in = (x * a + y) * 2;
      connect(source, g[in], 1);
    }
    ll flow = max_flow(g, source, sink);
    if (flow == b) {
      cout << "possible" << endl;
    } else {
      cout << "not possible" << endl;
    }
  }
}
