#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using mi = vector<vi>;
using ii = pair<int,int>;
using iii = tuple<int, int, int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

void mark(vi &d, int i, int j, int c) {
  d[i] |= c;
  d[j + 4] |= c;
  if (i == j) d[4 + 4] |= c;
  if (i + j == 3) d[4 + 4 + 1] |= c;
}

bool win(mi &m, int i, int j) {
  int c = m[i][j];
  bool win = true;
  for (int k = 0; k < 4; k++) win = win && (m[i][k] == c);
  if (win) return true;
  win = true;
  for (int k = 0; k < 4; k++) win = win && (m[k][j] == c);
  if (win) return true;
  if (i == j) {
    win = true;
    for (int k = 0; k < 4; k++) win = win && (m[k][k] == c);
    if (win) return true;
  }
  if (i + j == 3) {
    win = true;
    for (int k = 0; k < 4; k++) win = win && (m[k][3-k] == c);
    if (win) return true;
  }
  return false;
}

iii backtrack(mi &m, vi &d, int c, int level) {
  if (level > 6) return make_tuple(1, 0, 0);
  iii r(2, 0, 0);
  for (int i = 0; i < 4 && get<0>(r) == 2; i++) {
    for (int j = 0; j < 4 && get<0>(r) == 2; j++) {
      if (m[i][j] != 0) continue;
      vi td(d);
      mark(td, i, j, c);
      bool draw = true;
      for (auto k : td) if (k != 3) draw = false;
      if (draw) {
        r = make_tuple(1, i, j);
      }
    }
  }
  if (get<0>(r) == 1 && c != 1) return r;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (m[i][j] != 0) continue;
      vi td(d);
      mark(td, i, j, c);
      if (get<0>(r) == 1) {
        bool ok = false;
        ok = ok || (td[i] != 3);
        ok = ok || (td[j + 4] != 3);
        if (i == j) ok = ok || (td[8] != 3);
        if (i + j == 3) ok = ok || (td[9] != 3);
        if (!ok) continue;
      }
      m[i][j] = c;
      if (win(m, i, j)) {
        r = make_tuple(0, i, j);
      } else {
        auto opp = backtrack(m, td, 3 - c, level + 1);
        if (2 - get<0>(opp) < get<0>(r)) {
          r = make_tuple(2 - get<0>(opp), i, j);
        }
      }
      m[i][j] = 0;
      if (get<0>(r) == 0 || (get<0>(r) == 1 && c != 1)) return r;
    }
  }
  return r;
}

int main() {
  string s;
  while (cin >> s, s == "?") {
    vi d(10, 0);
    mi m(4);
    for (int i = 0; i < 4; i++) {
      m[i].resize(4, 0);
      cin >> s;
      for (int j = 0; j < 4; j++) {
        switch (s[j]) {
          case 'x': m[i][j] = 1; mark(d, i, j, 1); break;
          case 'o': m[i][j] = 2; mark(d, i, j, 2); break;
        }
      }
    }
    auto r = backtrack(m, d, 1, 0);
    if (get<0>(r) != 0) {
      printf("#####\n");
    } else {
      printf("(%d,%d)\n", get<1>(r), get<2>(r));
    }
  }
}
