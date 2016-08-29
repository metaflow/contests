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

llu P[25][151];

void prepare() {
  fill(&P[0][0], &P[25][0], 0);
  P[0][0] = 1;
  for (int n = 0; n < 24; ++n) {
    for (int i = 0; i < 151; ++i) {
      for (int t = 1; t <= 6 && t + i < 151; ++t) {
        // P[n + 1][i + t] += 1;
        P[n + 1][i + t] += P[n][i];
      }
    }

  }
  for (int n = 0; n < 25; ++n) {
    for (int i = 150; i > 0; --i) P[n][i - 1] += P[n][i];
  }

}

llu gcd(llu a, llu b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
  prepare();
  int n, x;
  while (cin >> n >> x, n) {
    llu a = P[n][x];
    llu b = P[n][0];
    llu g = gcd(a, b);
    a /= g; b /= g;
    if (b == 1) {
      printf("%llu\n", a);
    } else {
      printf("%llu/%llu\n", a, b);
    }
  }
}
//time : 17:18
