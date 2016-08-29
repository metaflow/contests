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

ll pow_mod(ll b, ll e, ll m) {
  if (e == 0) return 1;
  if (e % 2 == 0) {
    return pow_mod((b * b) % m, e / 2, m);
  }
  return (b * pow_mod(b, e - 1, m)) % m;
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; ++tc) {
    ll n, k, m;
    cin >> n >> k >> m;
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      sum += x;
    }
    ll r = (sum % m) * (k % m) * pow_mod(n, k - 1, m);
    r %= m;
    printf("Case %d: %lld\n", tc, r);
  }
}
