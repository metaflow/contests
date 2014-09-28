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
  int n, k, i;
  while (cin >> n >> k) {
    vi p(n);
    for (i = 0; i < n; ++i) cin >> p[i];
    sort(p.begin(), p.end());
    auto it = p.crbegin();
    llu s = 0;
    while (it != p.crend()) {
      s += *it - 1;
      for (int i = 0; i < k && it != p.crend(); ++i) it++;
    }
    cout << (s * 2) << endl;
  }
}
