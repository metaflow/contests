#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n, t;
  while (cin >> n >> t) {
    vi d(n);
    for (int i = 1; i < n; i++) cin >> d[i];
    queue<int> q;
    q.push(1);
    bool ok = false;
    while (!q.empty()) {
      int a = q.front(); q.pop();
      if (a == t) {
        ok = true;
        break;
      }
      if (a == n) break;
      q.push(a + d[a]);
    }
    if (ok) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
