#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  llu n, m;
  while (cin >> n >> m) {
    int f = 0, t = n - 1;
    vi r(n);
    llu k = 1;
    k <<= (n - 2);
    for (llu i = 1; i <= n; i++) {
      if (m > k) {
        r[t] = i;
        t--;
        m -= k;
      } else {
        r[f] = i;
        f++;
      }
      k >>= 1;
    }
    bool first = true;
    for (auto i : r) {
      if (!first) cout << " ";
      first = false;
      cout << i;
    }
    cout << endl;
  }
}
