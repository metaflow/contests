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

struct disjoint_set {
  vll parent;
  disjoint_set(size_t n) {
    parent.resize(n);
    for (size_t i = 0; i < n; i++) {
      parent[i] = i;
    }
  }
  ll get_parent(ll i) {
    if (parent[i] != i) parent[i] = get_parent(parent[i]);
    return parent[i];
  }
  bool connected(ll i, ll j) {
    return get_parent(i) == get_parent(j);
  }
  void connect(ll i, ll j) {
    ll a = get_parent(i);
    ll b = get_parent(j);
    parent[a] = b;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll v, e;
  while (cin >> v >> e) {
    disjoint_set ds(255);
    vector<ii> edges;
    for (ll i = 0; i < e; i++) {
      char a, b; cin >> a >> b;
      edges.emplace_back(a - 'A', b - 'A');
      ds.connect(edges.back().first, edges.back().second);
    }
    vii components(255);
    for (ll i = 0; i < 255; i++) components[ds.get_parent(i)].first++;
    for (auto q : edges) components[ds.get_parent(q.first)].second++;
    ll total = 1;
    for (auto c : components) {
      if (c.second == 0) continue;
      total += 1 + c.second - c.first;
    }
    cout << total << endl;
  }
}
