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

using ll = long long;
using vi = vector<ll>;
using ii = pair<int,int>;
using llu = unsigned long long;

int main() {
  int n;
  cin >> n;
  vi v(n);
  ll sum = 0;
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
    sum += v[i];
  }
  ll result = 0;
  if (sum % 3 == 0) {
    ll x = sum / 3;
    int c = 0;
    ll t = 0;
    for (int i = 0; i < n - 1; ++i) {
      t += v[i];
      if ((t == 2 * x) && (i > 0)) result += c;
      if (t == x) ++c;
    }
  }
  printf("%llu\n", result);
}
