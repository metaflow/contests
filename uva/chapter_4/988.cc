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
  int n;
  int tcc = 0;
  while (cin >> n) {
    if (tcc) cout << endl;
    ++tcc;
    vi c(n, 0);
    c[0] = 1;
    int total = 0;
    for (int i = 0; i < n; ++i) {
      int k;
      cin >> k;
      if (k == 0) {
        total += c[i];
        continue;
      }
      while (k--) {
        int u;
        cin >> u;
        c[u] += c[i];
      }
    }
    cout << total << endl;
  }
}
