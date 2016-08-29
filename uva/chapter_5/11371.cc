#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

ll vi_ll(vi &v) {
  ll a = 0;
  for (auto i : v) {
    a *= 10;
    a += i;
  }
  return a;
}

int main() {
  ll n;
  while (cin >> n) {
    vi d(10);
    while (n) {
      d[n % 10]++;
      n /= 10;
    }
    ll a = 0;
    for (int i = 9; i >= 0; i--) {
      for (int j = 0; j < d[i]; j++) {
        a *= 10;
        a += i;
      }
    }
    ll b = 0;
    for (int i = 1; i <= 9; i++) {
      if (d[i] == 0) continue;
      d[i]--;
      b = i;
      break;
    }
    for (int i = 0; i <= 9; i++) {
      for (int j = 0; j < d[i]; j++) {
        b *= 10;
        b += i;
      }
    }
    printf("%lld - %lld = %lld = 9 * %lld\n", a, b, a - b, (a - b) / 9);
  }
}
