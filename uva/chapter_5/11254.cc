#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  ll n;
  while (cin >> n, n != -1) {
    ll best = 1; ll f = n;
    for (ll k = 2;; k++) {
      ll a = 2 * n - k * (k - 1);
      ll b = a / (2 * k);
      if (b <= 0) break;
      if (a % (2 * k) == 0) {
        best = k;
        f = b;
      }
    }
    printf("%lld = %lld + ... + %lld\n", n, f, f + best - 1);
  }
}
