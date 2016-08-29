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
    int best = 0, best_size = 0;
    for (int i = 0; i < n; i++) {
      int a, b;
      cin >> a >> b;
      int t = min(a * 4, b);
      t = max(t, min(a * 2, b * 2));
      t = max(t, min(a , b * 4));
      if (t > best_size) {
        best = i;
        best_size = t;
      }
    }
    cout << (best + 1) << endl;
  }
}
