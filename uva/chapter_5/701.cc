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

long double pow_first(long double b, llu e) {
  if (e == 0) return 1;
  if (e % 2 == 0) {
    long double r = b * b;
    while (log10(r + 1) > 10) r /= 10;
    return pow_first(r, e / 2);
  } else {
    long double r = b * pow_first(b, e - 1);
    while (log10(r + 1) > 10) r /= 10;
    return r;
  }
}

bool check(ll e, ll n) {
  ll p = floor(pow_first(2, e));
  while (p > n) p /= 10;
  return p == n;
}

ll seek(int a) {
  if (a == 1) return 7;
  long double k = log2(a);
  long double k2 = log2(a + 1);
  llu f = ceil(log10(a + 1) + 1);
  for (ll t = f; t <= 10000000; ++t) {
    ll x = ceil(k + t * log2(10));
    ll y = ceil(k2 + t * log2(10));
    if (x > y) break;
    for (ll i = x; i < y; ++i) {
      if (check(i, a)) return i;
    }
  }
  return -1;
}

int main() {
  ll n;
  while (cin >> n) {
    auto r = seek(n);
    if (r < 0) {
      printf("no power of 2\n");
    } else {
      printf("%lld\n", r);
    }
  }
}

