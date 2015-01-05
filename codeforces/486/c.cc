#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n, p;
  while (cin >> n >> p) {
    p--;
    string s;
    cin >> s;
    int left = n / 2;
    int right = 0;
    if (p >= n / 2) p = n - p - 1;
    int cost = 0;
    for (int i = 0; i < n / 2; i++) {
      int d = s[i] - s[n - i - 1];
      if (d == 0) continue;
      left = min(left, i);
      right = max(right, i);
      if (d < 0) d += 26;
      cost += min(d, 26 - d);
    }
    if (cost != 0) {
      if (left <= p && right >= p) {
        cost += min(p - left, right - p) + (right - left);
      } else {
        if (right > p) {
          cost += right - p;
        } else {
          cost += p - left;
        }
      }
    }
    cout << cost << endl;
  }
}
