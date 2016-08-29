#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 101;
int height[MAX][MAX], dependent[MAX][MAX], path[MAX][MAX];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    string name; int w, h;
    cin >> name >> h >> w;
    fill(&dependent[0][0], &dependent[MAX][0], 0);
    fill(&path[0][0], &path[MAX][0], 1);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        cin >> height[i][j];
      }
    }
    queue<ii> q;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        for (int k = 0; k < 4; k++) {
          int a = i + dx[k];
          int b = j + dy[k];
          if (a < 0 || a >= h || b < 0 || b >= w) continue;
          if (height[i][j] > height[a][b]) dependent[i][j]++;
        }
        if (dependent[i][j] == 0) q.emplace(i, j);
      }
    }
    while (!q.empty()) {
      int i = q.front().first;
      int j = q.front().second;
      q.pop();
      for (int k = 0; k < 4; k++) {
        int a = i + dx[k];
        int b = j + dy[k];
        if (a < 0 || a >= h || b < 0 || b >= w) continue;
        if (height[i][j] < height[a][b]) {
          dependent[a][b]--;
          if (dependent[a][b] == 0) q.emplace(a, b);
          path[a][b] = max(path[a][b], path[i][j] + 1);
        }
      }
    }
    int best = 0;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        best = max(best, path[i][j]);
      }
    }
    printf("%s: %d\n", name.c_str(), best);
  }
}
