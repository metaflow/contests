#include <vector>
#include <list>
#include <map>
#include <set>
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
#include <queue>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

const int MAX = 2001;
const int INF = numeric_limits<int>::max();
int da[MAX][MAX], db[MAX][MAX];

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
  int n;
  while (cin >> n, n) {
    queue<ii> q;
    fill(&da[0][0], &da[MAX][0], INF);
    fill(&db[0][0], &db[MAX][0], INF);

    while (n--) {
      int x, y;
      cin >> x >> y;
      da[x][y] = 0;
      q.push(ii(x, y));
    }

    cin >> n;

    while (n--) {
      int x, y;
      cin >> x >> y;
      db[x][y] = 0;
      q.push(ii(x, y));
    }

    int d = INF;
    while (!q.empty()) {
      int x = q.front().first;
      int y = q.front().second;
      q.pop();
      if (da[x][y] != INF && db[x][y] != INF) {
        d = da[x][y] + db[x][y];
        break;
      }
      for (int i = 0; i < 4; ++i) {
        int x_ = x + dx[i];
        int y_ = y + dy[i];
        if (x_ < 0 || y_ < 0 || x_ >= MAX || y_ >= MAX) continue;
        if (da[x][y] != INF && da[x_][y_] == INF) {
          da[x_][y_] = da[x][y] + 1;
          q.push(ii(x_, y_));
        }
        if (db[x][y] != INF && db[x_][y_] == INF) {
          db[x_][y_] = db[x][y] + 1;
          q.push(ii(x_, y_));
        }
      }
    }

    cout << d << endl;
  }
}


