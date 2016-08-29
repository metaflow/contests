#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 101;

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n;
    cin >> n;
    vi c(MAX, 0);
    for (int i = 0; i < n * n; i++) {
      int a; cin >> a; c[a]++;
    }
    bool ok = true;
    for (int i = 0; i < MAX; i++) {
      if (c[i] > n) { ok = false; break; }
    }
    printf("Case %d: %s\n", tc, (ok ? "yes" : "no"));
  }
}
