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
  int n, s, tc = 0;
  while (cin >> n, n) {
    tc++;
    s = 0;
    vi v(n);
    while (n--) {
      cin >> v[n];
      s += v[n];
    }
    s /= v.size();
    int r = 0;
    for (auto i : v) if (i > s) r += i - s;
    printf("Set #%d\nThe minimum number of moves is %d.\n\n", tc, r);
  }
}
