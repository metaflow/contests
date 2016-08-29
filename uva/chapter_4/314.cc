#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
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
using iii = tuple<int, int, int>;
using ll = long long;
using llu = unsigned long long;
const int MAX = 50;
const int INF = numeric_limits<int>::max();

int m[MAX][MAX][4];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
  int r, c;
  while (cin >> r >> c, r) {
    fill(&m[0][0][0], &m[MAX][0][0], INF);
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
        int a;
        cin >> a;
        if (a == 0) continue;
        for (int k = 0; k < 4; ++k) {
          m[i][j][k] = -1;
          m[i][j + 1][k] = -1;
          m[i + 1][j][k] = -1;
          m[i + 1][j + 1][k] = -1;
        }
      }
    }

    int a, b, x, y;
    string s;
    cin >> a >> b >> x >> y >> s;
    iii start(a, b, 0);
    switch (s[0]) {
      case 'n': get<2>(start) = 0; break;
      case 'e': get<2>(start) = 1; break;
      case 's': get<2>(start) = 2; break;
      case 'w': get<2>(start) = 3; break;
    }
    queue<iii> q;
    m[a][b][get<2>(start)] = 0;
    q.push(start);
    int result = -1;
    while (!q.empty()) {
      auto p = q.front();
      q.pop();
      int a = get<0>(p);
      int b = get<1>(p);
      int d = get<2>(p);
      if (a == x && b == y) {
        result = m[a][b][d];
        break;
      }
      for (int i = 1; i <= 3; ++i) {
        int e = a + dx[d] * i;
        int f = b + dy[d] * i;
        if (e <= 0 || e >= r || f <= 0 || f >= c) break;
        if (m[e][f][d] == -1) break;
        if (m[e][f][d] == INF) {
          m[e][f][d] = m[a][b][d] + 1;
          q.push(iii(e, f, d));
        }
      }
      for (int i = 0; i < 2; ++i) {
        int g = (d + 1 - 2 * i + 4) % 4;
        if (m[a][b][g] == INF) {
          m[a][b][g] = m[a][b][d] + 1;
          q.push(iii(a, b, g));
        }
      }
    }
    cout << result << endl;
  }
}
