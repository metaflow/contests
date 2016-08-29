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
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n;
  int tc = 1;
  while (cin >> n, n) {
    vector<tuple<int, int, int>> points;
    for (int i = 0; i < n; i++) {
      int a, b, p; cin >> a >> b >> p;
      points.emplace_back(a, b, p);
    }
    int a, b, r;
    cin >> a >> b >> r;
    a--; b--;
    vector<tuple<int, int, int>> g1, g2;
    int x2 = get<0>(points[a]) - get<0>(points[b]);
    int y2 = get<1>(points[a]) - get<1>(points[b]);
    for (auto t : points) {
      int x1 = get<0>(points[a]) - get<0>(t);
      int y1 = get<1>(points[a]) - get<1>(t);
      if (get<2>(t) == 0) continue;
      if (x1 * y2 - x2 * y1 < 0) {
        g1.emplace_back(t);
      } else {
        g2.emplace_back(t);
      }
    }
    if (g1.size() > g2.size()) swap(g1, g2);
    vvb m(g1.size());
    for (size_t i = 0; i < g1.size(); i++) {
      m[i].resize(g2.size());
      for (size_t j = 0; j < g2.size(); j++) {
        if (get<2>(g1[i]) <= get<2>(g2[j])) continue;
        int x = get<0>(g1[i]) - get<0>(g2[j]);
        int y = get<1>(g1[i]) - get<1>(g2[j]);
        if (x * x + y * y > r * r) continue;
        m[i][j] = true;
      }
    }
    cout << "Case " << tc << ": " << bipartite_matching(m) << endl;
    tc++;
  }
}
