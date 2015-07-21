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

struct node {
  ll id, parent, level, in, out;
  vll adjusted;
};

void eulerian_path(vector<node>& g, const ll u, vll& path) {
  path.emplace_back(u);
  for (auto v : g[u].adjusted) {
    if (v == g[u].parent) continue;
    g[v].parent = u;
    g[v].level = g[u].level + 1;
    eulerian_path(g, v, path);
    path.emplace_back(u);
  }
}

ll rmq_size(ll index, ll from, ll to) {
  if (from == to) return index + 1;
  ll m = (from + to) / 2;
  return max(rmq_size(2 * index, from, m), rmq_size(2 * index + 1, m + 1, to));
}

void build_rmq(vll& rmq, vll& values, ll index, ll from, ll to) {
  if (from == to) {
    rmq[index] = from;
    return;
  }
  ll m = (from + to) / 2;
  ll l = 2 * index;
  ll r = l + 1;
  build_rmq(rmq, values, l, from, m);
  build_rmq(rmq, values, r, m + 1, to);
  if (values[rmq[l]] < values[rmq[r]]) {
    rmq[index] = rmq[l];
  } else {
    rmq[index] = rmq[r];
  }
}

ll query_rmq(vll& rmq, vll& values, ll index, ll from, ll to, ll a, ll b) {
  if (a <= from && b >= to) return rmq[index];
  if (from > b || to < a) return -1;
  ll m = (from + to) / 2;
  ll l = 2 * index;
  ll r = l + 1;
  ll li = query_rmq(rmq, values, l, from, m, a, b);
  ll ri = query_rmq(rmq, values, r, m + 1, to, a, b);
  if (li == -1) return ri;
  if (ri == -1) return li;
  if (values[li] < values[ri]) return li;
  return ri;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n;
    vector<node> g(n);
    for (ll i = 0; i < n; i++) {
      g[i].id = i;
      g[i].in = INF;
      g[i].out = -1;
      g[i].parent = -1;
    }
    for (ll i = 0; i < n - 1; i++) {
      ll a, b; cin >> a >> b; a--; b--;
      g[a].adjusted.emplace_back(b);
      g[b].adjusted.emplace_back(a);
    }

    vll e;
    g[0].level = 0;
    eulerian_path(g, 0, e);
    // for (auto i : e) cout << " " << i;
    // cout << endl;
    vll level(e.size());
    for (ll i = 0; i < e.size(); i++) {
      level[i] = g[e[i]].level;
      g[e[i]].in = min(g[e[i]].in, i);
      g[e[i]].out = max(g[e[i]].out, i);
    }
    vll rmq(rmq_size(1, 0, e.size() - 1));
    build_rmq(rmq, level, 1, 0, level.size() - 1);
    ll q; cin >> q;
    while (q--) {
      ll k; cin >> k;
      vll p(k);
      vector<bool> unvisited(n);
      ll a = INF, b = 0;
      for (ll i = 0; i < k; i++) {
        cin >> p[i];
        p[i]--;
        unvisited[p[i]] = true;
        a = min(a, g[p[i]].out);
        b = max(b, g[p[i]].in);
      }
      if (a == b) {
        cout << "Yes" << endl;
      } else {
        ll lca = query_rmq(rmq, level, 1, 0, level.size() - 1, a, b);
        lca = e[lca];
        // cout << e[a] << ".." << e[b] << " " << lca << endl;
        ll t = e[a];
        while (t >= 0) {
          unvisited[t] = false;
          if (t == lca) break;
          t = g[t].parent;
        }
        t = e[b];
        while (t >= 0) {
          unvisited[t] = false;
          if (t == lca) break;
          t = g[t].parent;
        }
        bool ok = true;
        for (auto b : unvisited) if (b) { ok = false; break; }
        if (ok) {
          cout << "Yes" << endl;
        } else {
          cout << "No" << endl;
        }
      }

    }
  }
}
