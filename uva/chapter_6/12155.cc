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

char tile(int x, int y, int n) {
  int t = n / 2;
  if (x > t) x = n - 1 - x;
  if (y > t) y = n - 1 - y;
  if (x + y - t < 0) return '.';
  // cerr << 2 * t - x - y << endl;
  return (char)('a' + (2 * t - x - y) % 26);
}

int main() {
  int n, r1, c1, r2, c2;
  int tcc = 0;
  while (cin >> n >> r1 >> c1 >> r2 >> c2, n) {
    printf("Case %d:\n", ++tcc);
    n = n * 2 - 1;
    for (int r = r1; r <= r2; ++r) {
      for (int c = c1; c <= c2; ++c)
        printf("%c", tile(r % n, c % n, n));
      printf("\n");
    }
  }
}

// time : 22:00
