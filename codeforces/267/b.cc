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

int set_bits(int i) {
   i = i - ((i >> 1) & 0x55555555);
   i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
   return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> v(m+1);
  for (int i = 0; i < m + 1; ++i) cin >> v[i];
  int x = v[m];
  int result = 0;
  for (int i = 0; i < m; ++i) {
    int d = x ^ v[i];
    if (set_bits(d) <= k) ++result;
  }
  cout << result << endl;
}
