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
  int p, q, f, t;
  cin >> p >> q >> f >> t;
  vector<bool> a(1001), b(1001);
  while (p--) {
    int x, y;
    cin >> x >> y;
    while (x <= y) {
      a[x] = true;
      ++x;
    }
  }

  while (q--) {
    int x, y;
    cin >> x >> y;
    while (x <= y) {
      b[x] = true;
      ++x;
    }
  }

  int r = 0;
  for (int shift = f; shift <= t; ++shift) {
    for (int i = shift; i < 1001; ++i) {
      if (a[i] && b[i - shift]) {
        ++r;
        break;
      }
    }
  }
  cout << r << endl;
}
