#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int MAX = 1000;
const int INF = numeric_limits<int>::max();

int ds[MAX][MAX], dd[MAX][MAX];
bool mine[MAX][MAX];

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
  int r, c;
  while (cin >> r >> c, r) {
    fill(&ds[0][0], &ds[MAX][0], INF);
    fill(&dd[0][0], &dd[MAX][0], INF);
    fill(&mine[0][0], &mine[MAX][0], false);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
      int k, h;
      cin >> k >> h;
      while (h--) {
        int x;
        cin >> x;
        mine[k][x] = true;
      }
    }
    int x, y;
    queue<ii> q;

    cin >> x >> y;
    ds[x][y] = 0;
    q.push(ii(x, y));

    cin >> x >> y;
    dd[x][y] = 0;
    q.push(ii(x, y));

    int result = INF;

    while (!q.empty()) {
      int x = q.front().first;
      int y = q.front().second;
      if (ds[x][y] != INF && dd[x][y] != INF) {
        result = ds[x][y] + dd[x][y];
        break;
      }
      q.pop();
      for (int i = 0; i < 4; ++i) {
        int x_ = x + dx[i];
        int y_ = y + dy[i];
        if (x_ < 0 || x_ >= r || y_ < 0 || y_ >= c) continue;
        if (mine[x_][y_]) continue;
        if (ds[x][y] != INF && ds[x_][y_] == INF) {
          ds[x_][y_] = ds[x][y] + 1;
          q.push(ii(x_, y_));
        }
        if (dd[x][y] != INF && dd[x_][y_] == INF) {
          dd[x_][y_] = dd[x][y] + 1;
          q.push(ii(x_, y_));
        }
      }
    }
    cout << result << endl;
  }
}


