#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  ll n;
  while (cin >> n, n) {
    ll s = floor(pow(n, 0.5));
    if ((s + 1) * (s + 1) < n) s++;
    int x = 1; int y = s;
    int at = s * s;
    // printf("@ %d %d %d\n", at, x, y);
    if (at < n) {
      y++; at++;
      while (x <= s && at < n) { at++; x++; }
      while (at < n) { at++; y--; }
    }
    if (s % 2 == 0) swap(x, y);
    printf("%d %d\n", x, y);
  }
}
