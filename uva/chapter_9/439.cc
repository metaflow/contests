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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string from, to;
  const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
  const int dy[] = {1, -1, 2, -2, 2, -2, 1, -1};
  int M = 8;
  int d[M][M];
  while (cin >> from >> to) {
    ii a, b;
    a.first = from[0] - 'a';
    a.second = from[1] - '1';
    b.first = to[0] - 'a';
    b.second = to[1] - '1';
    fill(&d[0][0], &d[M][0], INF);
    queue<ii> q;
    q.emplace(a);
    d[a.first][a.second] = 0;
    while (!q.empty() && d[b.first][b.second] == INF) {
      int x0, y0; tie(x0, y0) = q.front(); q.pop();
      for (ll i = 0; i < 8; i++) {
        int x = x0 + dx[i];
        int y = y0 + dy[i];
        if (x < 0 || x >= M || y < 0 || y >= M) continue;
        if (d[x][y] != INF) continue;
        d[x][y] = d[x0][y0] + 1;
        q.emplace(x, y);
      }
    }
    cout << "To get from " << from << " to " << to << " takes "
            << d[b.first][b.second] << " knight moves." << endl;
  }
}
