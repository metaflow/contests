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

const int MAX_CAMPUS = 601;

int memo[MAX_CAMPUS][301];
vi v;

int best(int k, int n) {
  if (n < 0) return 0;
  if (k < 0) return INF;
  int &r = memo[n][k];

  if (r == -1) {
    int sum = 0;
    r = INF;
    for (int i = n; i >= 0; --i) {
      sum += v[i];
      if (sum > r) break;
      r = min(r, max(sum, best(k - 1, i - 1)));
    }
  }
  return r;
}

int main() {
  int n, k;
  while (cin >> n >> k) {
    fill(&memo[0][0], &memo[MAX_CAMPUS][0], -1);
    ++n;
    v.resize(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    cout << best(k, n - 1) << endl;
  }
}
