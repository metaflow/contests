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
  ll n;
  cin >> n;
  ll f = 0;
  ll c = 0;
  while (true) {
    ++f;
    ll mink = f * (f - 1) / 2;
    if ((n - 2*f) / 3 < mink) break;
    if ((n - 2*f) % 3 != 0) continue;
    ++c;
  }
  cout << c << endl;
}
