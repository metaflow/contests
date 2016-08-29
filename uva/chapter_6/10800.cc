#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    printf("Case #%d:\n", tc);
    string s;
    cin >> s;
    int up = -INF, down = INF, current = 0;
    vi level;
    vi last(100);
    for (int i = 0; i < s.size(); i++) {
      char &c = s[i];
      switch (c) {
        case 'R': level.emplace_back(current); current++; c = '/'; break;
        case 'F': current--; level.emplace_back(current); c = '\\'; break;
        case 'C': level.emplace_back(current); c = '_'; break;
      }
      up = max(up, level.back());
      last[level.back() + 50] = i;
      down = min(down, level.back());
    }

    for (int i = up; i >= down; i--) {
      printf("| ");
      for (int j = 0; j < s.size(); j++) {
        if (j > last[i + 50]) break;
        if (level[j] == i) {
          printf("%c", s[j]);
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
    printf("+");
    for (int i = 0; i < s.size() + 2; i++) printf("-");
    printf("\n\n");
  }
}
