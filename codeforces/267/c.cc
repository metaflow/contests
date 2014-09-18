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

vi v;

const int MAX = 5002;

ll memo[MAX][MAX];

ll best(int n, int m, int k) {
  if (n < m * k) return -INF;
  if (k == 0) return 0;
  ll &r = memo[n][k];
  if (r == -1) {
    ll s = 0;
    for (int i = 0; i < m; ++i) {
      s += v[n - i - 1];
    }
    r = max(s + best(n - m, m, k - 1), best(n - 1, m, k));
  }
  return r;
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  fill(&memo[0][0], &memo[n + 1][0], -1);
  v.resize(n);
  for (int i = 0; i < n; ++i) cin >> v[i];
  cout << best(n, m, k) << endl;
}
