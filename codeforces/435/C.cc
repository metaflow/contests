#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;
const l MAX = 1002;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vector<vector<bool>> M(MAX, vb(2*MAX));
    l max_y = 0, min_y = 2 * MAX;
    l x = 0, y = MAX, dy = 1;
    for (l i = 0; i < n; i++) {
      l a; cin >> a;
      for (l j = 0; j < a; j++) {
        M[x][y] = true;
        max_y = max(max_y, y);
        min_y = min(min_y, y);
        x++;
        y += dy;
      }
      dy = -dy;
    }
    M[x][y] = true;
    max_y = max(max_y, y);
    min_y = min(min_y, y);
    for (l y = max_y; y > min_y; y--) {
      for (l i = 0; i < x; i++) {
        if (M[i + 1][y] && M[i][y - 1]) { cout << '/'; }
        else if (M[i][y] && M[i + 1][y - 1]) { cout << '\\'; }
        else cout << ' ';
      }
      cout << endl;
    }
  }
}
