#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

bool possible(ll n, ll k) {
  for (ll i = 0; i < k; i++) {
    if (n % k != 1) return false;
    n = (n - 1) / k * (k - 1);
  }
  return (n % k) == 0;
}

int main() {
  ll n;
  while (cin >> n, n != -1) {
    ll a = -1;
    for (ll i = 2; i * i <= n || i < 3; i++) {
      if (n % i != 1) continue;
      if (n / i == 0) break;
      if (possible(n, n / i)) a = max(a, n / i);
      if (possible(n, i)) a = max(a, i);
    }
    printf("%lld coconuts, ", n);
    if (a == -1) {
      printf("no solution\n");
    } else {
      printf("%lld people and 1 monkey\n", a);
    }
  }
}
