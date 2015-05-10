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
    int x, r, c;
    cin >> x >> r >> c;
    if (r > c) swap(r, c);
    bool richard = false;
    if (x == 2 * r) {
      richard = r > 1;// 2 or 3
    }
    if (x > c || (x > 2 * r) || (x > 7) || (r * c % x != 0)) richard = true;
    if (richard) {
      printf("Case #%d: RICHARD\n", tc);
    } else {
      printf("Case #%d: GABRIEL\n", tc);
    }
  }
}
