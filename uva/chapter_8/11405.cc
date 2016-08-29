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
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int m; cin >> m;
    int board[8][8];
    int pawn = 1;
    for (int i = 0; i < 8; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < 8; j++) {
        switch (s[j]) {
          case 'K':
          case 'p': board[i][j] = -1; break;
          case '.': board[i][j] = 0; break;
          case 'P': pawn++; board[i][j] = pawn; break;
          case 'k': board[i][j] = 1; break;
        }
      }
    }
    vvi distances(pawn);
    for (int i = 0; i < pawn; i++) {
      distances[i].resize(pawn, INF);
      distances[i][i] = 0;
    }
    //BFS from each p and k to find shortest paths
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (board[i][j] <= 0) continue;
        bool visited[8][8];
        fill(&visited[0][0], &visited[8][0], false);
        queue<tuple<int, int, int>> q;
        q.emplace(i, j, 0); visited[i][j] = true;
        while (!q.empty()) {
          auto p = q.front(); q.pop();
          int x0 = get<0>(p); int y0 = get<1>(p); int depth = get<2>(p) + 1;
          const int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
          const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
          for (int k = 0; k < 8; k++) {
            int x = x0 + dx[k];
            int y = y0 + dy[k];
            if (x < 0 || y < 0 || x >= 8 || y >= 8) continue;
            if (board[x][y] < 0 || visited[x][y]) continue;
            visited[x][y] = true;
            if (board[x][y] > 0) {
              distances[board[i][j] - 1][board[x][y] - 1] = depth;
            }
            q.emplace(x, y, depth);
          }
        }
      }
    }
    ll answer = tsp(distances);
    if (answer <= m && answer != INF) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
