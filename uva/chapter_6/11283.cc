#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

char board[16];
bool pairs[26][26];
int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[] = {1, 1, 1, 0, 0, -1, -1, -1};

bool find_from(string &s, int p, int x, int y) {
  if (p == s.size()) return true;
  if (s[p] != board[x * 4 + y]) return false;
  bool ok = false;
  char t = board[x * 4 + y];
  board[x * 4 + y] = '*';
  for (int i = 0; i < 8; i++) {
    int x_ = x + dx[i];
    if (x_ < 0 || x_ > 3) continue;
    int y_ = y + dy[i];
    if (y_ < 0 || y_ > 3) continue;
    ok = find_from(s, p + 1, x_, y_);
    if (ok) break;
  }
  board[x * 4 + y] = t;
  return ok;
}

bool find_word(string &s) {
  for (auto i = 0; i < s.size() - 1; i++) {
    if (pairs[s[i] - 'A'][s[i + 1] - 'A']) continue;
    return false;
  }
  for (int i = 0; i < 16; i++) {
    if (find_from(s, 0, i / 4, i % 4)) return true;
  }
  return false;
}

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    fill(&pairs[0][0], &pairs[26][0], false);
    for (int i = 0; i < 4; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < 4; j++) board[i * 4 + j] = s[j];
    }
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        for (int i = 0; i < 8; i++) {
          int x_ = x + dx[i];
          if (x_ < 0 || x_ > 3) continue;
          int y_ = y + dy[i];
          if (y_ < 0 || y_ > 3) continue;
          pairs[board[x * 4 + y] - 'A'][board[x_ * 4 + y_] - 'A'] = true;
        }
      }
    }
    int n;
    cin >> n;
    int score = 0;
    while (n--) {
      string s;
      cin >> s;
      if (find_word(s)) {
        switch (s.size()) {
          case 3:
          case 4: score++; break;
          case 5: score += 2; break;
          case 6: score += 3; break;
          case 7: score += 5; break;
          default: score += 11; break;
        }
      }
    }
    printf("Score for Boggle game #%d: %d\n", tc, score);
  }
}
