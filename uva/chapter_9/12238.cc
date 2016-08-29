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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

class StaticRMQ {
  vvll S;
public:
  StaticRMQ(vll& v) {
    ll n = v.size();
    S.resize(v.size());
    for (ll i = 0; i < n; i++) S[i].emplace_back(i);
    for (ll k = 1; (1 << k) <= n; k++) {
      for (ll i = 0; i + (1 << k) - 1 < n; i++) {
        ll a = S[i][k - 1];
        ll b = S[i + (1 << (k - 1))][k - 1];
        if (v[a] <= v[b]) {
          S[i].emplace_back(a);
        } else {
          S[i].emplace_back(b);
        }
      }
    }
  }

  // [from, to]
  size_t query(vll& v, size_t from, size_t to) {
    ll k = 0;
    while ((to - from + 1) >= (1 << (1 + k))) k++;
    ll a = S[from][k];
    ll b = S[to - (1 << k) + 1][k];
    if (v[a] <= v[b]) return a;
    return b;
  }
};

default_random_engine source(random_device{}());

ll random_in_range(ll a, ll b) {
  return uniform_int_distribution<ll>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  ll at = -1;
  ll depth = 0;
  ll id;
  vector<pedge> adjusted;
  pnode parent;
};

struct edge {
  pnode to;
  ll w;
};

void connect(pnode &a, pnode &b, ll w) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->to = b; ea->w = w;
  eb->to = a; eb->w = w;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

void dfs(pnode u, vll& path, vll& depths) {
  path.emplace_back(u->id);
  depths.emplace_back(u->depth);
  u->at = path.size() - 1;
  for (auto e : u->adjusted) {
    auto v = e->to;
    if (v->at == -1) {
      v->depth = u->depth + e->w;
      dfs(v, path, depths);
    }
    path.emplace_back(u->id);
    depths.emplace_back(u->depth);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n, n) {
    graph g(n);
    for (ll i = 0; i < n; i++) {
      g[i] = make_shared<node>();
      g[i]->id = i;
    }
    for (ll i = 0; i < n - 1; i++) {
      ll a, l;
      cin >> a >> l;
      connect(g[i + 1], g[a], l);
    }
    vll path;
    vll depths;
    dfs(g[0], path, depths);
    StaticRMQ rmq(depths);
    ll q; cin >> q;
    for (ll i = 0; i < q; i++) {
      if (i) cout << " ";
      ll s, t; cin >> s >> t;
      ll a = g[s]->at;
      ll b = g[t]->at;
      if (a > b) swap(a, b);
      auto f = rmq.query(depths, a, b);
      auto lca = g[path[f]];
      ll answer = g[s]->depth - lca->depth + g[t]->depth - lca->depth;
      cout << answer;
    }
    cout << endl;
  }
}
