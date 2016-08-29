#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n, m, c;
  while (cin >> n >> m >> c, n) {
    int t = (n - 7) * (m - 7);
    int b = t / 2;
    int w = t - b;
    if (c == 0) {
      cout << b << endl;
    } else {
      cout << w << endl;
    }
  }
}
