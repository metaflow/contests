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
  int n, i, count, tcc; bool f;
  cin >> tcc;
  while (tcc--) {
    cin >> n;
    vi v(n);
    for (i = 0; i < n; i++) cin >> v[i];
    count = 0;
    f = true;
    while (f) {
      f = false;
      for (i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
          swap(v[i], v[i + 1]);
          count++;
          f = true;
        }
      }
    }
    printf("Optimal train swapping takes %d swaps.\n", count);
  }
}
