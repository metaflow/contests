#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 501;

double dp[MAX][MAX];

double p;

double s(int n, int k);

double f(int n, int k) {
  if (k < 0 || n < 0) return 0;
  double &r = dp[n][k];
  if (r < 0) {
    if (k == 0) {
      return r = pow(1 - p, n);
    }
    if (n < k) {
       return r = f(n, n);
    }
    if (n == k) {
      return r = pow(p, n) + f(n, k - 1);
    }
    r = f(n - 1, k);
    if (n == k + 1) {
      r -= pow(p, n);
    } else if (n > k + 1) {
      r -= (1 - p) * pow(p, k + 1) * f(n - k - 2, k);
    }
  }
  return r;
}

int main() {
  int n;
  while (cin >> n >> p, n) {
    fill(&dp[0][0], &dp[MAX][0], 0);
    for (int i = 0; i <= n; i++) dp[0][i] = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        dp[i][j] = dp[i - 1][j];
        if (i == j + 1) dp[i][j] -= pow(p, j + 1);
        if (i > j + 1) dp[i][j] -= pow(p, j + 1) * (1 - p) * dp[i - 2 - j][j];
      }
    }
    double r = 0;
    for (int i = 0; i <= n; i++) {
      r += i * (dp[n][i] - dp[n][i - 1]);
    }
    printf("%.6f\n", r);
  }
}
