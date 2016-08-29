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

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

const int MAX = 100;
const int INF = numeric_limits<int>::max();
int d[MAX][MAX];

void floydWarshall(int n) {
  for (int k = 0; k < n; ++k)
  for (int i = 0; i < n; ++i)
  for (int j = i + 1; j < n; ++j)
    d[i][j] = d[j][i] = min(d[i][j], max(d[i][k], d[k][j]));
}

int main() {
  int n, m, q;
  int tc = 0;
  while (cin >> n >> m >> q, n) {
    if (tc) printf("\n");
    ++tc;
    fill(&d[0][0], &d[MAX][0], INF);
    while (m--) {
      int a, b, w;
      cin >> a >> b >> w;
      --a; --b;
      d[a][b] = d[b][a] = w;
    }
    floydWarshall(n);
    printf("Case #%d\n", tc);
    while (q--) {
      int a, b;
      cin >> a >> b;
      --a; --b;
      if (d[a][b] == INF) {
        printf("no path\n");
      } else {
        printf("%d\n", d[a][b]);
      }
    }
  }
}
