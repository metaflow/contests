#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n, k;
  while (cin >> n >> k, n >= 0) {
    vi a;
    for (int i = 0; i <= n; i++) { int x; cin >> x; a.emplace_back(x); }
    for (int i = n; i >= k; i--) {
      if (a[i] == 0) continue;
      a[i - k] -= a[i];
      a[i] = 0;
    }
    int t = n; while (t > 0 && a[t] == 0) t--;
    for (int i = 0; i <= t; i++) {
      if (i) printf(" ");
      printf("%d", a[i]);
    }
    printf("\n");
  }
}
