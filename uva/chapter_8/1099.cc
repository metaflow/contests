#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX_N = 15;
const int MAX_B = (1 << MAX_N);
const int MAX_H = 100;
const int MAX_V = MAX_H * MAX_H;

int sump[MAX_B];
int n;
int dpm[MAX_H + 1][MAX_B];
int parts[MAX_N];
int max_divisor[MAX_V + 1];

void sieve() {
  fill_n(max_divisor, MAX_V, 0);
  max_divisor[1] = 1;
  for (int i = 2; i <= MAX_V; i++) {
    if (max_divisor[i]) continue;
    for (int j = i; j <= MAX_V; j += i) max_divisor[j] = i;
  }
}

bool dp(int h, int b) {
  if (dpm[h][b] == 0) {
    int c = 0;
    int used[MAX_N];
    for (int i = 0; i < n; i++) {
      if (b & (1 << i)) {
        used[c] = i;
        c++;
      }
    }
    int a = sump[b];
    int w = a / h;
    if (c == 1) {
      dpm[h][b] = 1;
      dpm[w][b] = 1;
    } else {
      dpm[h][b] = -1;
      dpm[w][b] = -1;
       // iterate one half of sets
      for (int i = 1; i < (1 << (c - 1)); i++) {
        int m = 0;
        int dl = 0, dr = 0;
        for (int j = 0; j < c - 1; j++) {
          if (i & (1 << j)) {
            m = m | (1 << used[j]);
            dl = max(dl, max_divisor[parts[used[j]]]);
          } else {
            dr = max(dr, max_divisor[parts[used[j]]]);
          }
        }
        dr = max(dr, max_divisor[parts[used[c - 1]]]);
        int a_left = sump[m];
        if (a_left % h == 0) {
          int w_left = w * a_left / a;
          int w_right = w - w_left;
          if (max(w_left, h) >= dl &&
              max(w_right, h) >= dr &&
              dp(min(h, w_left), m) &&
              dp(min(h, w_right), b ^ m)) {
            dpm[h][b] = 1;
            dpm[w][b] = 1;
            break;
          }
        }
        if (a_left % w == 0) {
          int h_left = h * a_left / a;
          int h_right = h - h_left;
          if (max(h_left, w) >= dl &&
              max(h_right, w) >= dr &&
              dp(min(w, h_left), m) &&
              dp(min(w, h_right), b ^ m)) {
            dpm[h][b] = 1;
            dpm[w][b] = 1;
            break;
          }
        }
      }
    }
  }
  return dpm[h][b] == 1;
}

int main() {
  int w, h;
  int tc = 1;
  sieve();
  while (cin >> n, n) {
    cin >> w >> h;
    fill(&dpm[0][0], &dpm[MAX_H + 1][0], 0);
    int sum = 0;
    for (int i = 0; i < n; i++) {
      cin >> parts[i];
      sum += parts[i];
    }
    bool ok = (sum == w * h);
    if (ok) {
      for (int b = 1; b < (1 << n); b++) {
        int p = 0;
        for (int i = 0; i < n; i++) {
          if (b & (1 << i)) p += parts[i];
        }
        sump[b] = p;
      }
      ok = dp(h, (1 << n) - 1);
    }
    cout << "Case " << tc++ << ": ";
    if (ok) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
