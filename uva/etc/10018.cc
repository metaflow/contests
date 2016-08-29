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

int main() {
  ll tcc, n, k, j, i;
  cin >> tcc;
  while (tcc--) {
    cin >> n;
    for (i = 0; i < 1010; i++) {
      j = 0; k = n;
      while (k) {
        j = j * 10 + (k % 10);
        k /= 10;
      }
      if (j == n && i != 0) {
        printf("%lld %lld\n", i, n);
        break;
      }
      n += j;
    }
  }
}
