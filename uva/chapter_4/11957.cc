#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 100;
bool board[MAX][MAX];
ll memo[MAX][MAX];
int n;

bool valid(int x, int y) {
  return x >= 0 && y >= 0 && y < n && (!board[x][y]);
}

ll count(int x, int y) {
  if (x == 0) return 1;
  ll &r = memo[x][y];
  if (r == -1) {
    r = 0;
    if (valid(x - 1, y - 1)) {
      r += count(x - 1, y - 1);
    } else {
      if (valid(x - 2, y - 2)) r += count(x - 2, y - 2);
    }
    if (valid(x - 1, y + 1)) {
      r += count(x - 1, y + 1);
    } else {
      if (valid(x - 2, y + 2)) r += count(x - 2, y + 2);
    }
    r %= 1000007;
  }
  return r;
}

int main() {
  int tcc;
  scanf("%d", &tcc);
  for (int tc = 1; tc <= tcc; tc++) {
    scanf("%d", &n);
    fill(&board[0][0], &board[MAX][0], false);
    fill(&memo[0][0], &memo[MAX][0], -1);
    int x, y;
    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < n; j++) {
        switch (s[j]) {
          case 'W': x = i; y = j; break;
          case 'B': board[i][j] = true; break;
        }
      }
    }
    printf("Case %d: %lld\n", tc, count(x, y));
  }
}

