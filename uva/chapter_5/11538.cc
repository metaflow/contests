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
  ll n, m;
  llu s[1000001];
  s[0] = 0;
  for (ll i = 0; i <= 1000000; ++i) s[i] = s[i - 1] + i * (i - 1);
  while (cin >> n >> m, n) {
    if (m > n) swap(m, n); // m < n
    llu r = (n - 1 + m - 1) * m * n // from straights
            + 2 * (2 * s[m - 1] + (n - m + 1) * m * (m - 1)); // from diagonals
    cout << r << endl;
  }
}
