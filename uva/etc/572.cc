#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 110;

int main() {
  int m, n;
  int f[MAX][MAX];
  while (cin >> m >> n, m) {
    string s;
    for (int i = 0; i < m; i++) {
      cin >> s;
      for (int j = 0; j < n; j++) {
        f[i][j] = (s[j] == '*' ? 0 : 1);
      }
    }
    int c = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (f[i][j] == 0) continue;
        c++;
        queue<ii> q;
        q.emplace(i, j);
        f[i][j] = 0;
        while (!q.empty()) {
          ii p = q.front(); q.pop();
          for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
              int x = p.first + dx; int y = p.second + dy;
              if (x < 0 || x >= m || y < 0 || y >= n) continue;
              if (f[x][y] == 0) continue;
              q.emplace(x, y);
              f[x][y] = 0;
            }
          }
        }
      }
    }
    cout << c << endl;
  }
}
