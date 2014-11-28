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
    int w, r, m, s;
    cin >> w >> r >> m >> s;
    printf("Case #%d:\n", tc);
    if (m < 10) {
      if (w < 35 || r < 40) {
        printf("EMERGENCY\n");
        continue;
      }
      if (r > 60) {
        printf("NIGHTMARE\n");
        continue;
      }
      if (s > 8 * 3600) {
        printf("WAKE-UP\n");
        continue;
      }
    }
    printf("NOTHING\n");
  }
}
