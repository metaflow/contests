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
  int n, i;
  while (cin >> n) {
    vector<pair<string, string>> h(n);
    for (i = 0; i < n; ++i) {
      string a, b;
      cin >> a >> b;
      if (b < a) swap(a, b);
      h[i].first = a;
      h[i].second = b;
    }
    vi p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];
    string latest = h[p[0] - 1].first;
    bool ok = true;
    for (int i = 1; i < n; ++i) {
      if (latest < h[p[i] - 1].first) {
        latest = h[p[i] - 1].first;
        continue;
      }
      if (latest < h[p[i] - 1].second) {
        latest = h[p[i] - 1].second;
        continue;
      }
      ok = false;
      break;
    }
    if (ok) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
