#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 128;
int M, N;
int DP[1 << 22];
int O[MAX];

int read_object() {
  int r = 0;
  string s;
  cin >> s;
  for (int i = 0; i < M; i++) {
    r <<= 2;
    if (s[i] == '0') {
      r += 0b01;
    } else {
      r += 0b10;
    }
  }
  return r;
}

void print_object(int o) {
  for (int i = 0; i < M; i++) {
    switch ((o >> (i * 2)) & 0b11) {
      case 0b01: printf("0"); break;
      case 0b10: printf("1"); break;
      case 0b11: printf("*"); break;
      default: printf("?"); break;
    }
  }
  printf("\n");
}


int count_matching(int features) {
  int r = 0;
  for (int i = 0; i < N; i++) if ((O[i] & features) == O[i]) r++;
  // printf("count = %d for ", r); print_object(features);
  return r;
}

int depth(int features) {
  // print_object(features);
  int &r = DP[features];
  if (r == -1) {
    r = INF;
    for (int i = 0; i < M; i++) {
      int sh = i * 2;
      if ((features | (0b11 << sh)) != features) continue;
      int f1 = features ^ (0b01 << sh);
      int c1 = count_matching(f1);
      if (c1 == 0) continue;
      int f2 = features ^ (0b10 << sh);
      int c2 = count_matching(f2);
      if (c2 == 0) continue;
      int d1 = 0;
      if (c1 > 1) d1 = depth(f1);
      int d2 = 0;
      if (c2 > 1) d2 = depth(f2);
      r = min(r, 1 + max(d1, d2));
    }
  }
  return r;
}

int main() {
  while (cin >> M >> N, M | N) {
    for (int i = 0; i < N; i++) {
      O[i] = read_object();
      // print_object(O[i]);
    }
    if (N == 1) {
      printf("0\n");
    } else {
      int any = 0;
      for (int i = 0; i < M; i++) {
        any = (any << 2) + 0b11;
      }
      fill_n(DP, 1 << 22, -1);
      printf("%d\n", depth(any));
    }
  }
}
