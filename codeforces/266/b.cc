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
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

int main() {
  ll n, a, b;
  cin >> n >> a >> b;
  n *= 6;
  ll m = numeric_limits<ll>::max();
  ll x = 0, y;
  while (a * b <= n || x == 0) {
    ll d = n / b;
    if (n % b) ++d;
    d = max(d, a);
    if (m > d * b) {
      x = d;
      y = b;
      m = d * b;
    }
    d = n / a;
    if (n % a) ++d;
    d = max(d, b);
    if (m > d * a) {
      x = a;
      y = d;
      m = d * a;
    }
    ++a;
    ++b;
  }
  printf("%llu\n%llu %llu\n", m, x, y);
}
