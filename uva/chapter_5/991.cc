#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 11;

int dp[MAX];

int c(int n) {
  auto &r = dp[n];
  if (r == 0) {
    if (n < 2) return r = 1;
    for (int i = 0; i < n; i++) r += c(i) * c(n - i - 1);
  }
  return r;
}

int main() {
  int n;
  fill_n(dp, MAX, 0);
  bool newline = false;
  while (cin >> n) {
    if (newline) printf("\n");
    newline = true;
    printf("%d\n", c(n));
  }
}

// time 16m
