#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 5001;
const int MOD = 1000000007;
int b;
ll memo[MAX][MAX];

int main() {
  int n, a, k;
  while (cin >> n >> a >> b >> k) {
    if (a > b) { a = n - a + 1; b = n - b + 1; }
    fill(&memo[0][0], &memo[MAX][0], -1);
    for (int i = 1; i < b; i++) memo[i][0] = 1;
    for (int j = 1; j <= k; j++) {
      for (int i = 1; i < b; i++) memo[i][j - 1] += memo[i - 1][j - 1];
      for (int i = 1; i < b; i++) {
        int f = max(1, i - (b - i) + 1);
        memo[i][j] = (memo[b-1][j - 1] - memo[f-1][j-1])
                   - (memo[i][j-1] - memo[i-1][j-1]);
        memo[i][j] %= MOD;
      }
    }
    cout << memo[a][k] << endl;
  }
}
