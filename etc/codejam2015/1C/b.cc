#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 123;

int back[MAX];
double prob[26];
string keyboard;
string target;
int K, L, S;

void kmp() {
  int i = 0, j = -1;
  back[0] = -1;
  while (i < L) {
    while (j >= 0 && target[i] != target[j]) j = back[j];
    i++; j++;
    back[i] = j;
  }
}

double dp[MAX][MAX];

double expected(int from, int matched) {
  if (from >= S) return 0;
  double& r = dp[from][matched];
  if (r > -0.5) return r;
  r = 0;
  for (int i = 0; i < 26; i++) {
    double p = prob[i];
    if (p == 0) continue;
    char c = 'A' + i;
    int j = matched;
    while (j >= 0 && target[j] != c) j = back[j];
    j++;
    if (j == L) {
      r += p;
      j = back[j];
    }
    r += p * expected(from + 1, j);
  }
  return r;
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    fill(&dp[0][0], &dp[MAX][0], -1);
    cin >> K >> L >> S;
    cin >> keyboard;
    cin >> target;
    // target += '+';
    for (int i = 0; i < 26; i++) {
      prob[i] = 0;
      for (auto c : keyboard) {
        if (c == (char)('A' + i)) {
          prob[i] += 1.0 / K;
        }
      }
    }
    bool ok = true;
    for (auto c : target) {
      if (prob[c - 'A'] == 0) ok = false;
    }
    double ans = 0;
    if (ok) {
      kmp();
      int m;
      m = (S - back[L]) / (L - back[L]);
      ans = m - expected(0, 0);
    }

    printf("Case #%d: %.8f\n", tc, ans);
  }
}
