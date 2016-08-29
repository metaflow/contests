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
  int tcc, a, b, tc;
  cin >> tcc;
  for (tc = 1; tc <= tcc; tc++) {
    cin >> a >> b;
    a = a / 2;
    b = (b - 1) / 2;
    printf("Case %d: %d\n", tc, (a + b + 1) * (b - a + 1));
  }
}
