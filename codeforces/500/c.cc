#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n, m;
  while (cin >> n >> m) {
    vi w(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    vi d(m);
    vector<bool> used(n, false);
    stack<int> t;
    for (int i = 0; i < m; i++) {
      cin >> d[i];
      if (used[d[i]]) continue;
      t.push(d[i]);
      used[d[i]] = true;
    }
    stack<int> s;
    while (!t.empty()) {
      // cerr << t.top() << endl;
      s.push(t.top());
      t.pop();
    }
    int r = 0;
    for (int i = 0; i < m; i++) {
      int j = d[i];
      while (s.top() != j) {
        r += w[s.top() - 1];
        t.push(s.top());
        s.pop();
      }
      s.pop();
      while (!t.empty()) { s.push(t.top()); t.pop(); }
      s.push(j);
    }
    cout << r << endl;
  }
}
