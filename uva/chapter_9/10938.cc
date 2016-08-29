// tags: LCA, 2^k jumps, DP
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

struct node;
struct edge;
using pnode = shared_ptr<node>;
using graph = vector<pnode>;

struct node {
  vector<pnode> adjusted;
  pnode parent;
  ll depth, id;
  vector<pnode> jumps; // 1, 2, 4.., 2^k jumps up
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n, n) {
    graph g(n);
    for (ll i = 0; i < n; i++) {
      g[i] = make_shared<node>();
      g[i]->id = i + 1;
    }
    for (ll i = 0; i < n - 1; i++) {
      ll a, b; cin >> a >> b;
      a--; b--;
      g[a]->adjusted.emplace_back(g[b]);
      g[b]->adjusted.emplace_back(g[a]);
    }
    queue<pnode> q;
    q.emplace(g[0]);
    g[0]->depth = 0;
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      auto r = u->parent;
      ll k = 0;
      while (r) {
        u->jumps.emplace_back(r);
        if (k >= (ll)r->jumps.size()) break;
        r = r->jumps[k];
        k++;
      }
      for (auto v : u->adjusted) {
        if (v == u->parent) continue;
        v->depth = u->depth + 1;
        v->parent = u;
        q.emplace(v);
      }
    }

    ll l; cin >> l;
    for (ll i = 0; i < l; i++) {
      ll a, b; cin >> a >> b; a--; b--;
      auto q = g[a], w = g[b];
      auto u = q, v = w;
      // find lca
      // make equal depth
      if (u->depth < v->depth) swap(u, v);
      while (u->depth != v->depth) {
        ll k = 0;
        while (k + 1 < (ll)u->jumps.size() &&
               v->depth + (1 << (k + 1)) <= u->depth) k++;
        u = u->jumps[k];
      }
      // make safe jumps
      ll k = u->jumps.size() - 1;
      while (u != v) {
        while (k > 0 &&
          (k >= (ll)u->jumps.size() ||
          u->jumps[k] == v->jumps[k])) k--;
        u = u->jumps[k];
        v = v->jumps[k];
      }
      // find middle
      auto lca = u;
      ll d = q->depth - lca->depth + w->depth - lca->depth;
      u = (q->depth > w->depth) ? q : w;
      ll t = d / 2;
      while (t) {
        ll k = 0;
        while (k + 1 < (ll)u->jumps.size()
               && (t >= (1 << (k + 1)))) k++;
        u = u->jumps[k];
        t -= 1 << k;
      }
      if (d % 2) {
        ll r = u->id;
        ll p = u->parent->id;
        if (r < p) swap(r, p);
        cout << "The fleas jump forever between "
             << p << " and " << r << "." << endl;
      } else {
        cout << "The fleas meet at " << u->id << "." << endl;
      }
    }
  }
}
