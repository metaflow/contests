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
const int INF = numeric_limits<int>::max();

int memo[49][49][49][49];

int win(int n, int m, int r, int c) {
  int &x = memo[n][m][r][c];
  if (x == -1) {
    x = 0;
    for (int i = 1; i <= r; ++i) {
      x = 1 - win(n - i, m, r - i, c);
      if (x == 1) return 1;
    }
    for (int i = r + 1; i < n; ++i) {
      x = 1 - win(i, m, r, c);
      if (x == 1) return 1;
    }

    for (int i = 1; i <= c; ++i) {
      x = 1 - win(n, m - i, r, c - i);
      if (x == 1) return 1;
    }
    for (int i = c + 1; i < m; ++i) {
      x = 1 - win(n, i, r, c);
      if (x == 1) return 1;
    }
  }
  return x;
}

int main() {
  int tcc;
  cin >> tcc;
  fill(&memo[0][0][0][0], &memo[49][0][0][0], -1);
  memo[1][1][1][1] = 0;
  while (tcc--) {
    int m, n, r, c;
    cin >> m >> n >> r >> c;
    if (win(m, n, r, c)) {
      cout << "Gretel" << endl;
    } else {
      cout << "Hansel" << endl;
    }
  }
}

// time : 22:16
