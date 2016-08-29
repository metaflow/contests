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

const int MAX = 26;

int m[MAX][MAX], y[MAX][MAX];

int main() {
  int n;
  while (cin >> n, n) {
    fill(&m[0][0], &m[MAX][0], INF);
    fill(&y[0][0], &y[MAX][0], INF);
    for (int i = 0; i < n; ++i) {
      char a, d, f, t;
      int c;
      cin >> a >> d >> f >> t >> c;
      int (*r)[MAX][MAX] = &m;
      if (a == 'Y') r = &y;
      int fi = (int)(f - 'A');
      int ti = (int)(t - 'A');
      (*r)[fi][ti] = c;
      if (d == 'B') (*r)[ti][fi] = c;
    }

    for (int i = 0; i < MAX; ++i) {
      m[i][i] = 0;
      y[i][i] = 0;
    }

    for (int k = 0; k < MAX; ++k)
    for (int i = 0; i < MAX; ++i)
    for (int j = 0; j < MAX; ++j) {
      m[i][j] = min(m[i][j], m[i][k] + m[k][j]);
      y[i][j] = min(y[i][j], y[i][k] + y[k][j]);
    }

    char f, t;
    cin >> f >> t;

    int fi = (int)(f - 'A');
    int ti = (int)(t - 'A');

    vi places;
    int best = INF;
    for (int i = 0; i < MAX; ++i) {
      int v = y[fi][i] + m[ti][i];
      if (v < best) {
        best = v;
        places.clear();
      }
      if (v == best) {
        places.push_back(i);
      }
    }
    if (best == INF) {
      printf("You will never meet.\n");
    } else {
      printf("%d", best);
      for (auto i : places) {
        printf(" %c", (char)(i + 'A'));
      }
      printf("\n");
    }
  }
}


