#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 501;

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

uint M[MAX][MAX][4];
int D[MAX][MAX][4];

int main() {
  ios_base::sync_with_stdio(false);
  int rows, cols;
  while (cin >> rows >> cols) {
    fill(&M[0][0][0], &M[MAX][0][0], 0);
    fill(&D[0][0][0], &D[MAX][0][0], INF);
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        if (r == rows - 1 && c == cols - 1) break;
        string s;
        cin >> s;
        for (auto a : s) {
          int d = 0;
          switch (a) {
            case 'E': d = 1; break;
            case 'S': d = 2; break;
            case 'W': d = 3; break;
          }
          for (int i = 0; i < 4; i++) {
            M[r][c][i] = M[r][c][i] | (1u << ((d + i) % 4));
          }
        }
      }
    }
    queue<tuple<int, int, int>> q;
    q.emplace(0,0,0);
    D[0][0][0] = 0;
    while (!q.empty()) {
      auto t = q.front(); q.pop();
      int r = get<0>(t);
      int c = get<1>(t);
      int k = get<2>(t);
      if (r == rows - 1 && c == cols - 1) break;
      for (int i = 0; i < 4; i++) {
        if (M[r][c][k] & (1u << i)) {
          int r_ = r + dr[i];
          int c_ = c + dc[i];
          if (r_ < 0 || r_ >= rows || c_ < 0 || c_ >= cols) continue;
          int k_ = (k + 1) % 4;
          if (D[r_][c_][k_] != INF) continue;
          D[r_][c_][k_] = D[r][c][k] + 1;
          q.emplace(r_, c_, k_);
        }
      }
    }
    int best = INF;
    for (int i = 0; i < 4; i++) best = min(best, D[rows - 1][cols - 1][i]);
    if (best == INF) {
      cout << "no path to exit" << endl;
    } else {
      cout << best << endl;
    }
  }
}
