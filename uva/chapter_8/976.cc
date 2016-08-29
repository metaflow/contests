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

const int MAX = 1000;
int rows, columns, bridges, gap;

void flood_fill(vvi& M, int r, int c, int from_color, int to_color) {
  const int dr[] = {1, -1, 0, 0};
  const int dc[] = {0, 0, 1, -1};
  queue<ii> q;
  if (M.empty()) return;
  int max_x = M.size();
  int max_y = M[0].size();
  M[r][c] = to_color;
  q.emplace(r, c);
  while (!q.empty()) {
    auto p = q.front(); q.pop();
    for (int i = 0; i < 4; i++) {
      int x = p.first + dr[i];
      int y = p.second + dc[i];
      if (x < 0 || x >= max_x || y < 0 || y >= max_y) continue;
      if (M[x][y] != from_color) continue;
      M[x][y] = to_color;
      q.emplace(x, y);
    }
  }
}

int DP[MAX][101];

int dp(int c, int left, vi& distances) {
  if (left == 0) return 0;
  int &r = DP[c][left];
  if (r == 0) {
    // take
    r = distances[c] + dp(c - gap - 1, left - 1, distances);
    // or not if possible
    if (c > (gap + 1) * (left - 1)) {
      r = min(r, dp(c - 1, left, distances));
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  while (cin >> rows >> columns >> bridges >> gap) {
    string s;
    getline(cin, s);
    // fill(&M[0][0], &M[MAX][0], 0);
    vvi M(rows);
    for (int r = 0; r < rows; r++) {
      getline(cin, s);
      M[r].resize(columns);
      for (int c = 0; c < columns; c++) {
        if (s[c] == '#') M[r][c] = 1;
      }
    }
    flood_fill(M, 0, 0, 1, 2);
    flood_fill(M, rows - 1, 0, 1, 3);
    vi distances;
    for (int c = 0; c < columns; c++) {
      int last_r = 0, last_color = 2;
      int min_distance = rows;
      for (int r = 0; r < rows; r++) {
        if (M[r][c] == 0) continue;
        if (M[r][c] != last_color) {
          min_distance = min(min_distance, r - last_r - 1);
        }
        last_r = r;
        last_color = M[r][c];
      }
      distances.emplace_back(min_distance);
    }
    fill(&DP[0][0], &DP[MAX][0], 0);
    cout << dp(columns - 1, bridges, distances) << endl;
  }
}
