#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 101;
ll memo[MAX][MAX];

ll c(int n, int m) {
  ll &r = memo[n][m];
  if (r == -1) {
    if (m == 0 || m == n) {
      r = 1;
      return r;
    }
    r = c(n - 1, m) + c(n - 1, m - 1);
  }
  return r;
}

int main() {
  int n, m;
  fill(&memo[0][0], &memo[MAX][0], -1);
  while (cin >> n >> m, n) {
    printf("%d things taken %d at a time is %lld exactly.\n",
      n, m, c(n, m));
  }
}
