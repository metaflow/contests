#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int w, h, r1, r2;
  while (cin >> w >> h >> r1 >> r2, w) {
    int d = max(r1, r2) * 2;
    bool ok = (w >= d) && (h >= d);
    if (ok) {
      int r = r1 + r2;
      ok = (pow(w - r, 2) + pow(h - r, 2) - pow(r, 2) >= 0);
    }
    if (ok) {
      cout << "S" << endl;
    } else {
      cout << "N" << endl;
    }
  }
}
