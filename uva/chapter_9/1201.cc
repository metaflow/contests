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

struct ride {
  ll start, end, a, b, c, d;
};

bool bipartite_matching_connect(const int u, vvb& m, vi& to, vb& used) {
  for (size_t v = 0; v < to.size(); v++) {
    if (!m[u][v] || used[v]) continue;
    used[v] = true;
    if (to[v] == -1 || bipartite_matching_connect(to[v], m, to, used)) {
      to[v] = u;
      return true;
    }
  }
  return false;
}

// {A} => {B}, m[i][j] == A[i] -> B[j]
int bipartite_matching(vvb& m) {
  if (m.empty()) return 0;
  vi to(m[0].size(), -1);
  int result = 0;
  for (size_t u = 0; u < m.size(); u++) {
    vb used(to.size());
    if (bipartite_matching_connect(u, m, to, used)) result++;
  }
  return result;
}

int main() {
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n;
    scanf("%lld", &n);
    vvb connections(n, vb(n));
    vector<ride> rides;
    for (ll i = 0; i < n; i++) {
      ride r;
      ll h, m;
      scanf("%lld:%lld %lld %lld %lld %lld",
        &h, &m, &(r.a), &(r.b), &(r.c), &(r.d));
      r.start = h * 60 + m;
      r.end = r.start + abs(r.a - r.c) + abs(r.b - r.d);
      for (ll j = 0; j < i; j++) {
        ride &q = rides[j];
        if (q.end + abs(r.a - q.c) + abs(r.b - q.d) < r.start) {
          connections[j][i] = true;
        }
      }
      rides.emplace_back(r);
    }
    printf("%lld\n", n - bipartite_matching(connections));
  }
}
