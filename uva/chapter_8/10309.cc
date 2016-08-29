#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int SIZE = 10;

uint F[SIZE];
int c = 0;

void turn(int row, int column) {
  if (column == 0) {
    F[row] = F[row] ^ 3u;
  } else {
    F[row] = (F[row] ^ (7u << (column - 1))) & ((1u << SIZE) - 1);
  }
  // for (int i = max(0, column - 1); i < min(SIZE, column + 2); i++) {
  //   F[row] = F[row] ^ (1u << i);
  // }
  if (row + 1 < SIZE) F[row + 1] = F[row + 1] ^ (1u << column);
  c++;
}

void print_F() {
  for (int i = 0; i < SIZE; i++) printf("%x\n", F[i]);
}

int main() {
  string name;
  while (cin >> name, name != "end") {
    for (int i = 0; i < SIZE; i++) {
      string s; cin >> s;
      F[i] = 0;
      for (int j = 0; j < SIZE; j++) {
        if (s[j] == 'O') F[i] = F[i] | (1u << j);
      }
    }
    // print_F();
    int best = 101;
    for (uint r = 0; r < (1u << SIZE); r++) {
      c = 0;
      uint t[SIZE]; for (int i = 0; i < SIZE; i++) t[i] = F[i];
      for (int i = 0; i < SIZE; i++) {
        if (r & (1u << i)) turn(0, i);
      }
      for (int i = 1; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
          if (F[i - 1] & (1u << j)) turn(i, j);
        }
      }
      if (F[SIZE - 1] == 0) best = min(best, c);
      swap(t, F);
    }
    if (best == 101) best = -1;
    cout << name << " " << best << endl;
  }
}
