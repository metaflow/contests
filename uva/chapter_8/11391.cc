#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int R, C;

ll M[1 << 16];

bool is_set(int mask, int x, int y) {
  return (mask & (1 << (x * 4 + y))) != 0;
}

int flip(int mask, int x, int y) {
  return mask ^ (1 << (x * 4 + y));
}

ll dp(int mask) {
  ll &r = M[mask];
  if (r == -1) {
    r = 0;
    for (int p = 0; p < 16; p++) {
      if ((mask & (1 << p)) == 0) continue;
      int x0 = p / 4;
      int y0 = p % 4;
      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          if (dx == 0 && dy == 0) continue;
          int x = x0 + 2 * dx; int y = y0 + 2 * dy;
          if (x < 0 || x >= R || y < 0 || y >= C) continue;
          if (!is_set(mask, x0 + dx, y0 + dy)) continue;
          if (is_set(mask, x, y)) continue;
          int m = flip(mask, x0, y0);
          m = flip(m, x0 + dx, y0 + dy);
          m = flip(m, x, y);
          r += dp(m);
        }
      }
    }
  }
  return r;
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n;
    cin >> R >> C >> n;
    int mask = 0;
    for (int i = 0; i < n; i++) {
      int x, y; cin >> x >> y; x--; y--;
      mask = flip(mask, x, y);
    }
    fill_n(M, 1 << 16, -1);
    for (int i = 0; i < 16; i++) {
      M[1 << i] = 1;
    }
    printf("Case %d: %lld\n", tc, dp(mask));
  }
}
