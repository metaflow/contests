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
  int n;
  cin >> n;
  vi v(n);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
    sum += v[i];
  }
  ll result = 0;
  if (sum % 3 == 0) {
    int x = sum / 3;
    int c = 0;
    int t = 0;
    for (int i = 0; i < n - 1; ++i) {
      t += v[i];
      if ((t == 2 * x) && (i > 0)) result += c;
      if (t == x) ++c;
    }
  }
  printf("%llu\n", result);
}
