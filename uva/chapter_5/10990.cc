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

const int MAX = 2000001;

int p[MAX];
int dp[MAX];
ll ds[MAX];

void sieve() {
  for (int i = 2; i < MAX; ++i) p[i] = i;
  for (int i = 2; i < MAX; ++i) {
    if (p[i] != i) continue;
    for (int j = 2 * i; j < MAX; j += i) p[j] = (p[j] / i) * (i - 1);
  }
}

int phi(int i) {
  if (p[i] == i) return i - 1;
  return p[i];
}

int depth(int n) {
  if (n == 1) return 0;
  if (dp[n] == 0) dp[n] = depth(phi(n)) + 1;
  return dp[n];
}

void precompute() {
  fill_n(dp, MAX, 0);
  ds[1] = 0;
  for (int i = 2; i < MAX; ++i) {
    ds[i] = ds[i - 1] + depth(i);
  }
}

ll sum(int a, int b) {
  return ds[b] - ds[a - 1];
}

int main() {
  sieve();
  precompute();
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n, m;
    cin >> n >> m;
    cout << sum(n, m) << endl;
  }
}
