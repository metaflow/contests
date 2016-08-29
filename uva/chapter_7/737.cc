#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  while (cin >> n, n) {
    int x1, x2, y1, y2, z1, z2;
    int x, y, z, d;
    cin >> x >> y >> z >> d;
    x1 = x; x2 = x + d;
    y1 = y; y2 = y + d;
    z1 = z; z2 = z + d;
    for (int i = 1; i < n; i++) {
      cin >> x >> y >> z >> d;
      x1 = max(x1, x); x2 = min(x2, x + d); x2 = max(x1, x2);
      y1 = max(y1, y); y2 = min(y2, y + d); y2 = max(y1, y2);
      z1 = max(z1, z); z2 = min(z2, z + d); z2 = max(z1, z2);
    }
    printf("%d\n", (x2 - x1) * (y2 - y1) * (z2 - z1));
  }
}
