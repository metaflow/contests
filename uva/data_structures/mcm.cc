// sudo apt-get install graphviz
//./mcm | dot -Tpng >mcm.png

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

const int MAX_SIZE = 20;

// unweigted max graph matching (Edmind's blossom algorithm)
// to filter edges modify node.out method
namespace unweighted_max_matching {
  struct node;
  struct edge;
  using pnode = shared_ptr<node>;
  using pedge = shared_ptr<edge>;
  using graph = vector<pnode>;

  ll _edge_id = 0;
  struct edge {
    pnode _to;
    pedge opposite;
    bool matched, visited;
    ll id;
    pnode to();
    pnode from() { return opposite->to(); }
    void match(bool v);
    void visit(bool v) { visited = v; opposite->visited = v; }
  };
  ll _node_id;
  struct node {
    ll id, age, tree_no, blossom_id;
    bool exposed;
    vector<pedge> adjusted;
    pedge back, matched;
    pnode up;
    vector<pnode> down;
    vector<pedge> _out;
    bool out_cached = false;
    vector<pedge> out() {
      if (!out_cached) {
        _out.clear();
        if (down.empty()) {
          for (auto e : adjusted) {
            // filter here
            _out.emplace_back(e);
          }
        } else {
          for (auto u : down) {
            for (auto e : u->out()) {
              auto v = e->to();
              auto r = e->from();
              if (v == r) continue;
              _out.emplace_back(e);
            }
          }
        }
        out_cached = true;
      }
      return _out;
    };
    void reset() {
      age = 0;
      tree_no = 0;
      back = NULL;
      up = NULL;
      out_cached = false;
      down.clear();
      for (auto e : adjusted) e->matched = false;
    }
    vector<pedge> path_to_root() {
      if (!back) return vector<pedge>();
      auto p = back->from()->path_to_root();
      p.emplace_back(back);
      return p;
    }
  };

  pnode edge::to() {
    auto t = _to;
    while (t->up) t = t->up;
    return t;
  }

  void edge::match(bool v) { matched = v; opposite->matched = v; }

  void connect(pnode &a, pnode &b) {
    pedge ea = make_shared<edge>();
    pedge eb = make_shared<edge>();
    _edge_id++;
    ea->id = _edge_id; ea->_to = b; ea->opposite = eb;
    eb->id = _edge_id; eb->_to = a; eb->opposite = ea;
    a->adjusted.emplace_back(ea);
    b->adjusted.emplace_back(eb);
  }

  vector<pedge> find_augmenting_path(graph& g);
  ll _blossom_id = 0;
  vector<pedge> process_blossom(graph& g, const pedge connect) {
    // create blossom
    _blossom_id++;
    ll blossom_id = _blossom_id;
    auto blossom = make_shared<node>();
    blossom->id = _node_id++;
    set<ll> blossom_border;
    blossom_border.insert(connect->id);
    auto u = connect->from();
    auto w = connect->to();
    while (u != w) {
      if (u->age < w->age) swap(u, w);
      blossom->down.emplace_back(u);
      blossom_border.insert(u->back->id);
      u = u->back->from();
    }
    blossom->down.emplace_back(u);
    for (auto v : blossom->down) {
      v->up = blossom;
      v->blossom_id = blossom_id;
    }
    // find augmented path with blossom
    g.emplace_back(blossom);
    auto path = find_augmenting_path(g);
    g.pop_back();
    // lift path: adding even-length path within blossom end-to-end or to exposed
    pnode target;
    for (auto v : blossom->down) {
      v->up = NULL;
      v->age = 0;
      v->back = NULL;
      if (v->exposed) target = v;
    }
    vector<pnode> border;
    for (auto e : path) {
      if (e->to()->blossom_id == blossom_id) border.emplace_back(e->to());
      if (e->from()->blossom_id == blossom_id) border.emplace_back(e->from());
    }
    if (border.empty()) return path;
    if (border.size() == 2) target = border[1];
    queue<pnode> q;
    q.emplace(border[0]);
    border[0]->age = 1;
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      for (auto e : u->out()) {
        if (blossom_border.count(e->id) == 0) continue;
        auto v = e->to();
        if (v->age != 0) continue;
        if (v == target && u->age % 2 == 1) continue;
        v->back = e;
        v->age = u->age + 1;
        q.emplace(v);
      }
    }
    auto b = target->path_to_root();
    path.insert(path.end(), b.begin(), b.end());
    return path;
  }

  queue<pnode> get_exposed(graph& g) {
    ll tree_no = 1;
    queue<pnode> q;
    for (auto u : g) {
      if (u->up) continue;
      u->age = 0;
      u->tree_no = 0;
      u->back = NULL;
      u->exposed = true;
      for (auto e : u->out()) {
        e->visit(false);
        if (e->matched) {
          u->exposed = false;
          u->matched = e;
        }
      }
      if (!u->exposed) continue;
      u->tree_no = tree_no++;
      q.emplace(u);
    }
    return q;
  }

  pnode add_to_tree(pedge e) {
    //    e
    // u --- v === w
    auto u = e->from();
    auto v = e->to();
    v->back = e;
    v->age = u->age + 1;
    auto y = v->matched;
    y->visit(true);
    pnode w = y->to();
    w->back = y;
    w->age = u->age + 2;
    v->tree_no = w->tree_no = u->tree_no;
    return w;
  }

  vector<pedge> connect_trees(pedge e) {
    vector<pedge> path;
    path.emplace_back(e);
    auto p = e->from()->path_to_root();
    path.insert(path.end(), p.begin(), p.end());
    p = e->to()->path_to_root();
    path.insert(path.end(), p.begin(), p.end());
    return path;
  }

  vector<pedge> find_augmenting_path(graph& g) {
    queue<pnode> q = get_exposed(g);
    vector<pedge> path;
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      for (auto e : u->out()) {
        if (e->visited) continue;
        e->visit(true);
        auto w = e->to();
        if (w->tree_no == 0) { q.emplace(add_to_tree(e)); continue; }
        if (w->age % 2 == 1) continue;
        if (w->tree_no != u->tree_no) return connect_trees(e);
        return process_blossom(g, e);
      }
    }
    return path;
  }

  ll match(graph& g) {
    for (auto u : g) u->reset();
    while (true) {
      auto p = find_augmenting_path(g);
      if (p.empty()) break;
      for (auto e : p) e->match(!e->matched);
    }
    ll r = 0;
    for (auto u : g) {
      for (auto e : u->adjusted) {
        if (e->matched) r++;
      }
    }
    return r / 2;
  }
}
using namespace unweighted_max_matching;
// - unweighted graph matching

default_random_engine source(random_device{}());

ll random_int(ll a, ll b) {
  return uniform_int_distribution<ll>(a, b)(source);
}

double random_double(double a, double b) {
  return uniform_real_distribution<double>(a, b)(source);
}

bool random_bool() {
  return random_int(0, 1) == 1;
}

graph random_graph() {
  double connectivity = random_double(0, 1);
  ll size = random_int(1, MAX_SIZE);
  graph g(size);
  for (ll i = 0; i < size; i++) {
    g[i] = make_shared<node>();
    g[i]->id = _node_id;
    _node_id++;
  }
  for (ll i = 0; i < size; i++) {
    for (ll j = i + 1; j < size; j++) {
      if (random_double(0, 1) > connectivity) continue;
      connect(g[i], g[j]);
    }
  }
  return g;
}

pair<ll, pedge> dp(graph& g, llu mask, map<llu, pair<ll, pedge>>& memo) {
  if (memo.count(mask)) {
    return memo[mask];
  }
  memo[mask].first = 0;
  memo[mask].second = NULL;
  if (mask == 0) return memo[mask];
  ll i = 0;
  auto t = mask;
  while ((t & (1ull << i)) == 0) i++;
  t = t ^ (1ull << i);
  memo[mask] = dp(g, t, memo); // don't take
  for (auto e : g[i]->out()) {
    ll j = e->to()->id;
    if ((t & (1ull << j)) == 0) continue;
    auto c = dp(g, t ^ (1ull << j), memo);
    c.first++;
    c.second = e;
    if (c.first > memo[mask].first) memo[mask] = c;
  }
  return memo[mask];
}

ll max_dp_matching(graph& g) {
  for (auto u : g) u->reset();
  llu mask = (1ull << g.size()) - 1;
  map<llu, pair<ll, pedge>> memo;
  auto r = dp(g, mask, memo);
  while (true) {
    auto p = dp(g, mask, memo);
    if (!p.second) break;
    p.second->match(true);
    mask = mask ^ (1ull << p.second->to()->id);
    mask = mask ^ (1ull << p.second->from()->id);
  }
  return r.first;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll a, b;
  for (ll i = 0; i < 1000; i++) {
    ll random_seed = random_device{}();
    // ll random_seed = 553835326; visualize = true;
    source.seed(random_seed);
    _node_id = 0;
    auto g = random_graph();
    a = max_dp_matching(g);
    b = match(g);
    if (a != b) {
      cout << "seed = " << random_seed << endl;
      cout <<  "exposed " << a << " but " << b << endl;
      break;
    }
  }
}
