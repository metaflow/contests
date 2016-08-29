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
  string name;
  while (cin >> name) {
    cout << name << endl;
    int n, k;
    cin >> n >> k;
    vi a(k, 0), b(k, INF);
    for (int i = 0; i < n - 1; ++i) {
      for (int j = 0; j < k; ++j) {
        for (int h = 0; h < k; ++h) {
          int v;
          cin >> v;
          b[h] = min(b[h], a[j] + v);
        }
      }
      a.swap(b);
      b.assign(k, INF);
    }
    int m = a[0];
    for (int i = 1; i < k; ++i) m = min(m, a[i]);
    cout << (m + (n - 1) * 2) << endl;
  }
}
