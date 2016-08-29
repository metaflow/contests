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
using iii = tuple<int, int, int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max() / 2;

const int MAX = 21;

double w[MAX][MAX][MAX];
ii path[MAX][MAX][MAX];

stack<int> solution;

void add_path(int from, int to, int d) {
  // printf("%d %d %d\n", from, to, d);
  if (d <= 0) return;
  if (d == 1) {
    solution.push(to);
    return;
  }
  ii p = path[from][to][d];
  int dk = p.second;
  int k = p.first;
  add_path(k, to, d - dk);
  add_path(from, k, dk);
}

int main() {
  int n;
  while (cin >> n) {
    fill(&w[0][0][0], &w[MAX][0][0], 0);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        path[i][j][1] = ii(i, 1);
        if (j == i) {
          w[i][j][0] = 1.0;
        } else {
          cin >> w[i][j][1];
        }
      }
    }

    bool f = false;

    for (int d = 2; d <= n && !f; ++d) {
      for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        for (int dk = 1; dk < d; ++dk) {
          double t = w[i][k][dk] * w[k][j][d - dk];
          if (w[i][j][d] >= t) continue;
          w[i][j][d] = t;
          path[i][j][d] = ii(k, dk);
        }
      }
      for (int i = 0; i < n; ++i) {
        if (w[i][i][d] <= 1.01) continue;
        f = true;
        add_path(i, i, d);
        solution.push(i);
        break;
      }
    }

    if (solution.empty()) {
      printf("no arbitrage sequence exists\n");
    } else {
      printf("%d", solution.top() + 1); solution.pop();
      while (!solution.empty()) {
        printf(" %d", solution.top() + 1); solution.pop();
      }
      printf("\n");
    }
  }
}
