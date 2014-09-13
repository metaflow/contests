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

const int MAX = 2001;
ll memo[MAX][MAX];
int v[MAX];
const ll D = 1000000007;

ll ways(int i, int p) {
  if (p < 0 || i < 0) return 0;
  ll &r = memo[i][p];
  if (r == -1) {
    r = 0;
    if (p == v[i]) {
      r += ways(i - 1, p) + ways(i - 1, p - 1);
    }
    if (p == v[i] - 1) {
      r += ways(i - 1, p) * 2 + ways(i - 1, p + 1) ;
    }
    r %= D;
  }
  return r;
}

int main() {
  int n, h;
  cin >> n >> h;
  fill(&memo[0][0], &memo[MAX][0], -1);
  memo[0][0] = 1;
  v[0] = 0;
  for (int i = 1; i <= n; ++i) cin >> v[i];
  for (int i = 0; i <= n; ++i) v[i] = h - v[i];
  printf("%lld\n", ways(n, 0));
}
