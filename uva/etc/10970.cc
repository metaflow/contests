#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 301;
int memo[MAX][MAX];

int main() {
  //fill(&memo[0][0], &memo[MAX][0], INF);
  memo[1][1] = 0;
  for (int i = 1; i < MAX; i++) {
    for (int j = 1; j < MAX; j++) {
      if (i == 1 && j == 1) continue;
      int &r = memo[i][j]= INF;
      for (int k = 1; k < i; k++) {
        r = min(r, memo[i - k][j] + memo[k][j]);
      }
      for (int k = 1; k < j; k++) {
        r = min(r, memo[i][j - k] + memo[i][k]);
      }
      r++;
    }
  }
  int n, m;
  while (cin >> n >> m) {
    cout << memo[n][m] << endl;
  }
}
