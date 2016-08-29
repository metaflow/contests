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
  printf("%d\n", tcc);
  for (int tc = 0; tc < tcc; tc++) {
    int r = random_in_range(1, 4);
    int c = random_in_range(1, 4);
    bool board[4][4];
    int n = 0;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        board[i][j] = random_bool();
        if (board[i][j]) n++;
      }
    }
    printf("%d %d %d\n", r, c, n);
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (board[i][j]) printf("%d %d\n", i + 1, j + 1);
      }
    }
  }
}
