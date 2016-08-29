/*
random cases are rarely leads to 'Yes' so this RIG filters generated cases to
get 1 to 1 ratio of 'Yes' and 'No'
*/


#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

default_random_engine source(random_device{}());

int random_in_range(int a, int b) {
  return uniform_int_distribution<>(a, b)(source);
}

bool random_bool() {
  return random_in_range(0, 1) == 1;
}

const int MAX_N = 15;
const int MAX_B = (1 << MAX_N) - 1;
const int MAX_H = 100;

int sump[MAX_B + 1];
int n;
int dpm[MAX_H + 1][MAX_B + 1];
int parts[MAX_N];

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
    if (c == 1) {
      dpm[h][b] = 1;
    } else {
      dpm[h][b] = -1;
      int a = sump[b];
      int w = a / h;
       // iterate one half of sets
      for (int i = 1; i < (1 << (c - 1)); i++) {
        int m = 0;
        for (int j = 0; j < c - 1; j++) {
          if (i & (1 << j)) m = m | (1 << used[j]);
        }
        int t = sump[m];
        if (t % h == 0) {
          if (dp(h, m) && dp(h, b ^ m)) {
            dpm[h][b] = 1;
            break;
          }
        }
        if (t % w == 0) {
          if (dp(w, m) &&
              dp(w, b ^ m)) {
            dpm[h][b] = 1;
            break;
          }
        }
      }
    }
  }
  return dpm[h][b] == 1;
}

int main() {
  int tcc = 50;
  for (int tc = 0; tc < tcc; tc++) {
    bool expected = random_bool();
    while (true) {
      n = random_in_range(1, 15);
      int x = random_in_range(1, 100);
      int y = random_in_range(1, 100);
      int left = x * y;
      if (left < n) continue;
      for (int i = 0; i < n - 1; i++) {
        parts[i] = random_in_range(1, left - (n - i - 1));
        left -= parts[i];
      }
      parts[n - 1] = left;
      for (int b = 1; b < (1 << n); b++) {
        int p = 0;
        for (int i = 0; i < n; i++) {
          if (b & (1 << i)) p += parts[i];
        }
        sump[b] = p;
      }
      fill(&dpm[0][0], &dpm[MAX_H + 1][0], 0);
      if (dp(x, (1 << n) - 1) == expected) {
        printf("%d\n%d %d\n", n, x, y);
        for (int i = 0; i < n; i++) {
          if (i) printf(" ");
          printf("%d", parts[i]);
        }
        printf("\n");
        break;
      }
    }
  }
  printf("0\n");
}
