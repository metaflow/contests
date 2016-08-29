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

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int MAX = 101;

int dxn[] = {1, -1, 0, 0, 1, -1, 0, 0};
int dym[] = {1, -1, 0, 0, -1, 1, 0, 0};
int dxm[] = {0, 0, 1, -1, 0, 0, 1, -1};
int dyn[] = {0, 0, 1, -1, 0, 0, -1, 1};

int main() {
  int tcc;
  int field[MAX][MAX];
  cin >> tcc;
  for (int tc = 1; tc <= tcc; ++tc) {
    int r, c, m, n, w;
    int odd_count = 0, even_count = 0;
    fill(&field[0][0], &field[MAX][0], 0);
    cin >> r >> c >> m >> n >> w;
    if (m > n) swap(m, n); // m < n
    while (w--) {
      int x, y;
      cin >> x >> y;
      field[x][y] = -1;
    }
    queue<ii> q;
    q.push(make_pair(0, 0));
    int uniq = 0;
    while (!q.empty()) {
      uniq++;
      ii pos = q.front(); q.pop();
      int count = 0;
      for (int i = 0; i < 8; ++i) {
        ii next = make_pair(pos.first  + dxn[i] * n + dxm[i] * m,
                            pos.second + dyn[i] * n + dym[i] * m);
        if (next.first < 0 || next.first >= r) continue;
        if (next.second < 0 || next.second >= c) continue;
        int &v = field[next.first][next.second];
        if (v == -1 || v == uniq) continue;
        count++;
        if (v == 0) q.push(next);
        v = uniq;
      }
      if (count % 2 == 0) {
        even_count++;
      } else {
        odd_count++;
      }
      field[pos.first][pos.second] = 1;
    }
    printf("Case %d: %d %d\n", tc, even_count, odd_count);
  }
}


