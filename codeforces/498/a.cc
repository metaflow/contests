#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  ll x1, y1, x2, y2;
  while (cin >> x1) {
    cin >> y1 >> x2 >> y2 >> n;
    int r = 0;
    while (n--) {
      ll a, b, c;
      cin >> a >> b >> c;
      bool b1 = (x1 * a + y1 * b + c) > 0;
      bool b2 = (x2 * a + y2 * b + c) > 0;
      if (b1 ^ b2) r++;
    }
    cout << r << endl;
  }
}

