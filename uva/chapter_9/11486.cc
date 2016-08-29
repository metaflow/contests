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
using state = tuple<ll, ll, ll, ll>;

const ll MOD = 1000000007;

vvll bfs(ll a1, ll a2, ll a3, ll a4) {
  map<state, ll> m;
  auto t = make_tuple(a1, a2, a3, a4);
  m[t] = m.size() - 1;
  //cerr << m[make_tuple(a1, a2, a3, a4)] << endl;
  queue<state> q;
  q.emplace(t);
  vvll adjustment(1);
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    auto p = m[u];
    for (ll d1 = 0; d1 < 2; d1++)
    for (ll d2 = 0; d2 < 2; d2++)
    for (ll d3 = 0; d3 < 2; d3++)
    for (ll d4 = 0; d4 < 2; d4++) {
      auto v = make_tuple(
        get<0>(u) + 1 - 2 * d1,
        get<1>(u) + 1 - 2 * d2,
        get<2>(u) + 1 - 2 * d3,
        get<3>(u) + 1 - 2 * d4);
      if (get<0>(v) < 0 || get<0>(v) > 6) continue;
      if (get<1>(v) < 0 || get<1>(v) > 6) continue;
      if (get<2>(v) < 0 || get<2>(v) > 6) continue;
      if (get<3>(v) < 0 || get<3>(v) > 6) continue;
      bitset<7> b;
      b.set(get<0>(v));
      b.set(get<1>(v));
      b.set(get<2>(v));
      b.set(get<3>(v));
      if (b.count() != 4) continue;
      if (m.count(v) == 0) {
        m[v] = m.size() - 1;
        q.emplace(v);
        adjustment.resize(m.size());
      }
      adjustment[p].emplace_back(m[v]);
    }
  }
  auto n = m.size();
  vvll g(n);
  for (size_t i = 0; i < n; i++) g[i].resize(n);
  for (size_t i = 0; i < n; i++) {
    for (auto j : adjustment[i]) g[j][i] = 1;
  }
  return g;
}

vvll matrix_multiply(vvll a, vvll b) {
  ll n = a.size();
  ll k = b.size();
  ll m = b[0].size();
  vvll c(n);
  for (ll i = 0; i < n; i++) c[i].resize(m);
  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < m; j++) {
      for (ll q = 0; q < k; q++) {
        c[i][j] = (c[i][j] + a[i][q] * b[q][j]) % MOD;
      }
    }
  }
  return c;
}

vvll matrix_power(vvll m, ll power) {
  ll n = m.size();
  vvll o(n);
  for (ll i = 0; i < n; i++) { o[i].resize(n); o[i][i] = 1; }
  while (power) {
    if (power % 2) o = matrix_multiply(o, m);
    m = matrix_multiply(m, m);
    power /= 2;
  }
  return o;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n;
    vll v(4);
    cin >> n;
    for (ll i = 0; i < 7; i++) {
      ll a; cin >> a;
      if (a) v[a - 1] = i;
    }
    auto g = bfs(v[0], v[1], v[2], v[3]);
    ll m = g.size();
    vvll start(m);
    for (ll i = 0; i < m; i++) start[i].emplace_back(0);
    start[0][0] = 1;
    auto finish = matrix_multiply(matrix_power(g, n - 1), start);
    ll answer = 0;
    for (auto v : finish) for (auto i : v) answer = (answer + i) % MOD;
    cout << answer << endl;
  }
}


