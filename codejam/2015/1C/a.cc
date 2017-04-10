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
    int r, c, w; cin >> r >> c >> w;
    int ans = (c / w) * r + w - 1;
    if (c % w) ans++;
    printf("Case #%d: %d\n", tc, ans);
  }
}
