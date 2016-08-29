#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const size_t SPACE = 1u << 26;
const int FULL_DICE = (1u << 6) - 1;

int D[SPACE];
const int dr[] = {0, 0, 1, -1};
const int dc[] = {1, -1, 0, 0};
const int rolls[][6] = {
  {1,2,3,0,4,5},
  {3,0,1,2,4,5},
  {4,1,5,3,2,0},
  {5,1,4,3,0,2}};

uint roll(uint dice, int d) {
  uint r = 0;
  for (int i = 0; i < 6; i++) {
    if (dice & (1u << rolls[d][i])) {
      r = r | (1u << i);
    }
  }
  return r;
}

uint encode(uint field, uint r, uint c, uint dice) {
  return field | (r << 16) | (c << 18) | (dice << 20);
}

int main() {
  fill_n(D, SPACE, INF);
  queue<tuple<uint, int, int, uint>> q;
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      q.emplace(0, r, c, FULL_DICE);
      uint t = encode(0, r, c, FULL_DICE);
      D[t] = 0;
    }
  }

  while (!q.empty()) {
    auto state = q.front(); q.pop();
    uint field = get<0>(state);
    int r = get<1>(state);
    int c = get<2>(state);
    uint dice = get<3>(state);
    // if (encode(field, r, c, dice) != t) { cerr << "!" << endl; }
    // printf("%x: field %x dice %x at %d %d\n", t, field, dice, r, c);
    for (int i = 0; i < 4; i++) {
      int r_ = r + dr[i];
      int c_ = c + dc[i];
      if (r_ < 0 || r_ > 3 || c_ < 0 || c_ > 3) continue;
      // jump before roll as we move backwards
      uint field_ = field;
      uint dice_ = dice;
      int d = dice_ & 1u;
      int x = r * 4 + c;
      int f = (field_ >> x) & 1u;
      if (d != f) {
        dice_ = dice_ ^ 1u;
        field_ = field_ ^ (1u << x);
      }
      dice_ = roll(dice_, i);
      uint next = encode(field_, r_, c_, dice_);
      if (D[next] != INF) continue;
      D[next] = D[encode(field, r, c, dice)] + 1;
      q.emplace(field_, r_, c_, dice_);
    }
  }

  int tcc;
  cin >> tcc;
  while (tcc--) {
    int dice_r = 0, dice_c = 0;
    uint field = 0;
    for (int r = 0; r < 4; r++) {
      string s;
      cin >> s;
      for (int c = 0; c < 4; c++) {
        switch (s[c]) {
          case 'D': dice_r = r; dice_c = c; break;
          case 'X': field = field | (1u << (r * 4 + c)); break;
        }
      }
    }

    uint t = encode(field, dice_r, dice_c, 0);
    // printf("%x\n", t);

    if (D[t] == INF) {
      cout << "impossible" << endl;
    } else {
      cout << D[t] << endl;
    }
  }
}
