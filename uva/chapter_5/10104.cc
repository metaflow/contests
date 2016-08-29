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

ll x, y, d;

void euclid(ll a, ll b) {
  if (b == 0) {
    x = 1;
    d = a;
    y = 0;
    return;
  }
  euclid(b, a % b);
  ll x0 = y;
  ll y0 = x;
  x = x0;
  y = y0 - a / b * x0;
}

void solve(ll a, ll b) {
  euclid(a, b);

  ll t1 = - x * d / b;
  ll t2 = y * d / a;

  if (t2 < t1) swap(t1, t2);

  ll bx = x, by = y;
  ll ab = abs(bx) + abs(by);
  for (ll t = t1 - 1; t <= t2 + 1; ++t) {
    ll tx = x + b / d * t;
    ll ty = y - a / d * t;
    ll at = abs(tx) + abs(ty);
    if ((at < ab) || ((at == ab) && (tx <= ty))) {
      bx = tx;
      by = ty;
    }
  }
}

int main() {
  ll a, b;
  while (cin >> a >> b) {
    solve(a, b);
    printf("%lld %lld %lld\n", x, y, d);
  }
}
