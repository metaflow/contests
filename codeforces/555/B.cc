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

struct point { ll x, y; };

bool bipartite_matching_connect(const int u,
  vector<point>& ranges, vll& bridges, vi& to, vb& used) {
  ll a = ranges[u].x;
  ll b = ranges[u].y;
  for (ll v = a; v <= b; v++) {
    if (used[v]) continue;
    if (to[v] == -1) {
      to[v] = u;
      return true;
    }
  }
  for (ll v = a; v <= b; v++) {
    if (used[v]) continue;
    used[v] = true;
    if (bipartite_matching_connect(to[v], ranges, bridges, to, used)) {
      to[v] = u;
      return true;
    }
  }
  return false;
}

// {A} => {B}, m[i][j] == A[i] -> B[j]
pair<vi, bool> bipartite_matching(vector<point>& ranges, vll& bridges) {
  vi to(bridges.size(), -1);
  for (size_t u = 0; u < ranges.size(); u++) {
    vb used(to.size());
    if (!bipartite_matching_connect(u, ranges, bridges, to, used))
      return make_pair(to, false);
  }
  return make_pair(to, true);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, m;
  while (cin >> n >> m) {
    vector<point> islands(n);
    for (ll i = 0; i < n; i++) cin >> islands[i].x >> islands[i].y;
    vector<pair<ll, ll>> bridges(m);
    for (ll i = 0; i < m; i++) {
      cin >> bridges[i].first;
      bridges[i].second = i;
    }
    sort(bridges.begin(), bridges.end());
    vll br(m);
    for (ll i = 0; i < m; i++) br[i] = bridges[i].first;
    vector<point> ranges(n - 1);
    bool ok = true;
    for (ll i = 0; i < n - 1; i++) {
      ranges[i].x = islands[i + 1].x - islands[i].y;
      ranges[i].y = islands[i + 1].y - islands[i].x;
      auto p = lower_bound(br.begin(), br.end(), ranges[i].x);
      if (p == br.end()) {ok = false ; break;}
      auto q = upper_bound(br.begin(), br.end(), ranges[i].y);
      while (q != br.end() && q != br.begin() && *q > ranges[i].y) q--;
      if (q == br.begin() && *q > ranges[i].y) {ok = false; break;}
      ll a = p - br.begin();
      ll b = q - br.begin();
      b = min(b, ll(br.size() - 1));
      ranges[i].x = a;
      ranges[i].y = b;
    }
    if (!ok || ranges.size() > bridges.size()) {
      cout << "No" << endl;
      continue;
    }
    auto answer = bipartite_matching(ranges, br);
    if (answer.second) {
      cout << "Yes" << endl;
      auto to = answer.first;
      vi assignment(n - 1);
      for (ll i = 0; i < m; i++) {
        if (to[i] == -1) continue;
        assignment[to[i]] = bridges[i].second + 1;
      }
      for (ll i = 0; i < n - 1; i++) {
        if (i) cout << " ";
        cout << assignment[i];
      }
      cout << endl;
    } else {
      cout << "No" << endl;
    }
    // break;
  }
}
