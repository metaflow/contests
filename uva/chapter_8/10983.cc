#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

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
  int original_flow;
  pedge opposite;
  int price;
};

void connect(pnode &a, pnode &b, int w, int price) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->original_flow = w; ea->opposite = eb;
  ea->price = price;
  eb->from = b; eb->to = a; eb->original_flow = 0; eb->opposite = ea;
  eb->price = price;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

int adjust(pedge e, int d) {
  if (!e) return d;
  d = adjust(e->from->back, min(d, e->flow));
  e->flow -= d;
  e->opposite->flow += d;
  return d;
}

ll max_flow(vector<pnode> &g, pnode &source, pnode &sink, int max_price) {
  ll result = 0;
  while (true) {
    for (auto u : g) u->age = 0;
    queue<pnode> q;
    q.push(source); source->age = 1;
    while (!(q.empty() || sink->age != 0)) {
      auto u = q.front(); q.pop();
      for (auto e : u->adjusted) {
        auto v = e->to;
        if (v->age != 0 || e->flow == 0 || e->price > max_price) continue;
        v->back = e;
        v->age = u->age + 1;
        q.push(v);
      }
    }
    if (sink->age == 0) break;
    for (auto e : sink->adjusted) {
      auto o = e->opposite;
      if ((e->to->age != sink->age - 1) ||
           e->price > max_price
           || o->flow == 0) continue;
      result += adjust(o, o->flow);
    }
  }
  return result;
}

// invariant: answer is within (a, b], f(a) = false, f(b) = true
ll binary_search_lower(ll a, ll b, function<bool(ll)> f) {
  while (b - a > 1) {
    ll m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

const int MAX = 30;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n, d;
    cin >> n >> d;
    graph g;
    pnode source = make_shared<node>();
    g.emplace_back(source);
    pnode city_day[MAX][MAX];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= d; j++) {
        city_day[i][j] = make_shared<node>();
        g.emplace_back(city_day[i][j]);
        if (j) connect(city_day[i][j - 1], city_day[i][j], INF, 0);
      }
    }
    int m; cin >> m;
    vi prices;
    for (int i = 0; i < m; i++) {
      int u, v, c, p, e;
      cin >> u >> v >> c >> p >> e;
      u--; v--;
      connect(city_day[u][e], city_day[v][e + 1], c, p);
      prices.emplace_back(p);
    }
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      int z; cin >> z;
      sum += z;
      connect(source, city_day[i][0], z, 0);
    }
    auto sink = city_day[n - 1][d];
    sort(prices.begin(), prices.end());
    auto test = [&] (ll x) {
      int price = 0;
      if (x >= 0) {
        price = prices[x];
      }
      for (auto u : g) for (auto e : u->adjusted) e->flow = e->original_flow;
      return max_flow(g, source, sink, price) == sum;
    };
    if (!test(prices.size() - 1)) {
      cout << "Case #" << tc << ": Impossible" << endl;
    } else {
      ll i = binary_search_lower(-2, prices.size() - 1, test);
      ll answer = 0;
      if (i >= 0) answer = prices[i];
      cout << "Case #" << tc << ": " << answer << endl;
    }
  }
}
