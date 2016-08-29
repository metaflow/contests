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
#include <queue>
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
const int INF = numeric_limits<int>::max() / 2;

const int MAX = 100;

int w[MAX][MAX];

int main() {
  int tcc = 0;
  while (true) {
    ++tcc;
    int a, b;
    fill(&w[0][0], &w[MAX][0], INF);
    int n = 0;
    while (cin >> a >> b, a != 0) {
      ++n;
      --a; --b;
      w[a][b] = 1;
    }
    if (n == 0) break;

    for (int k = 0; k < MAX; ++k)
    for (int i = 0; i < MAX; ++i)
    for (int j = 0; j < MAX; ++j)
      w[i][j] = min(w[i][j], w[i][k] + w[k][j]);

    double sum = 0.0;
    n = 0;
    for (int i = 0; i < MAX; ++i)
    for (int j = 0; j < MAX; ++j)
      if (i != j && w[i][j] != INF) {
        sum += w[i][j];
        ++n;
      }

    sum = round(sum / n * 1000) / 1000;
    printf("Case %d: average length between pages = %.3f clicks\n", tcc, sum);
  }
}
