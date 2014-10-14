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

const ll MOD = 1000000007;

int main() {
  llu a, b;
  while (cin >> a >> b) {
    llu r = b * (b - 1) / 2;
    r %= MOD;
    llu x = a;
    llu y = b + 2 + a * b;
    if (x % 2 == 0) {
      x /= 2;
    } else {
      y /= 2;
    }
    x %= MOD;
    y %= MOD;
    r = (r * x) % MOD;
    r = (r * y) % MOD;
    cout << r << endl;
  }
}
