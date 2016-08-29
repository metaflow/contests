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

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size() - 1)];
  }
  return s;
}

int main() {
  int tcc = 10;
  for (int tc = 0; tc < tcc; tc++) {
    int m = random_in_range(1, 11);
    int n = random_in_range(1, min(128, 1 << m));
    printf("%d %d\n", m, n);
    bitset<(1 << 11)> used;
    for (int i = 0; i < n; i++) {
      int v = random_in_range(0, (1 << m) - 1);
      while (used[v]) v = (v + 1) % (1 << m);
      used[v] = true;
      for (int j = 0; j < m; j++) {
        if (v & (1 << j)) {
          printf("1");
        } else {
          printf("0");
        }
      }
      printf("\n");
    }
  }
  printf("0 0\n");
}
