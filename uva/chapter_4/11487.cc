#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 10;
const int MOD = 20437;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
  int tc = 0;
  char m[MAX][MAX];
  int age[MAX][MAX];
  int w[MAX][MAX];
  int n;
  while (cin >> n, n) {
    tc++;
    vector<ii> pos(27, {-1, -1});
    for (int i = 0; i < n; i++) {
      string line;
      cin >> line;
      for (int j = 0; j < n; j++) {
        m[i][j] = line[j];
        if (m[i][j] >= 'A' && m[i][j] <= 'Z') {
          pos[m[i][j] - 'A'] = make_pair(i, j);
        }
      }
    }
    int to = 1;
    auto a = pos[0];
    auto b = pos[to];
    ll ways = 1;
    ll lenght = 0;
    while (b.first != -1) {
      int ax = a.first, ay = a.second;
      int bx = b.first, by = b.second;
      m[ax][ay] = '.';
      fill(&age[0][0], &age[MAX][0], INF);
      fill(&w[0][0], &w[MAX][0], 0);
      queue<ii> q;
      q.emplace(a); age[ax][ay] = 0; w[ax][ay] = 1;
      while (!q.empty()) {
        auto u = q.front(); q.pop();
        if (u == b) break;
        int ux = u.first, uy = u.second;
        for (int i = 0; i < 4; i++) {
          int vx = ux + dx[i];
          int vy = uy + dy[i];
          if (vx < 0 || vx >= n || vy < 0 || vy >= n) continue;
          if (m[vx][vy] != '.' && m[vx][vy] != ('A' + to)) continue;
          if (age[vx][vy] <= age[ux][uy]) continue;
          w[vx][vy] = (w[vx][vy] + w[ux][uy]) % MOD;
          if (age[vx][vy] == INF) {
            age[vx][vy] = age[ux][uy] + 1;
            q.emplace(vx, vy);
          }
        }
      }
      if (age[bx][by] == INF) {
        lenght = INF;
        break;
      }
      lenght += age[bx][by];
      ways = (ways * w[bx][by]) % MOD;
      a = b;
      to++;
      b = pos[to];
    }
    if (lenght == INF) {
      printf("Case %d: Impossible\n", tc);
    } else {
      printf("Case %d: %lld %lld\n", tc, lenght, ways);
    }
  }
}

