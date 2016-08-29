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
    for (int i = 1; ; i++) {
      queue<int> q;
      for (int j = 1; j <= n; j++) q.push(j);
      while (true) {
        if (q.front() == 13) break;
        q.pop();
        for (int j = 1; j < i; j++) { q.push(q.front()); q.pop(); }
      }
      if (q.size() == 1) {
        cout << i << endl;
        break;
      }
    }
  }
}
