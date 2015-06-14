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

// IDA* TSP with bitmask up to 64 vertices
ll ida_updated_bound;
ll estimate(int root, llu visited, vvi& distances) {
  ll e = 0;
  for (size_t i = 0; i < distances.size(); i++) {
    if (visited & (1ull << i)) continue;
    if (distances[root][i] > e) e = distances[root][i];
  }
  return e;
}

bool tsp_dfs(int position, llu visited, ll traveled,
             ll bound, vvi& distances) {
  ll e = estimate(position, visited, distances) + traveled;
  if (e > bound) {
    ida_updated_bound = min(ida_updated_bound, e);
    return false;
  }
  if (visited + 1 == (1ull << (distances.size()))) return true;
  for (size_t i = 0; i < distances.size(); i++) {
    if (visited & (1ull << i)) continue;
    if (tsp_dfs(i, visited | (1ull << i), traveled + distances[position][i],
                bound, distances)) return true;
  }
  return false;
}

ll tsp(vvi& distances) {
  ll bound = estimate(0, 1, distances);
  while (bound != INF) {
    ida_updated_bound = INF;
    if (tsp_dfs(0, 1, 0, bound, distances)) break;
    bound = ida_updated_bound;
  }
  return bound;
}



int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {

    ll answer = 0;
    cout << "Case #" << tc << ": " << answer << endl;
  }
}
