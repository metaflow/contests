#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

ll x, y, d;

void euclid(ll a, ll b) {
  if (b == 0) {
    x = 1; y = 0; d = a;
    return;
  }
  euclid(b, a % b);
  ll t = x;
  x = y;
  y = t - a / b * y;
}

int main() {
  ll n, a, b, ca, cb;
  while (cin >> n, n) {
    cin >> ca >> a >> cb >> b;
    euclid(a, b);
    if (n % d == 0) {
      x *= n / d;
      y *= n / d;
      ll f = - x * d / b;
      if (x * d % b != 0 && f >= 0) f++;
      ll t = y * d / a;
      if (y * d % a != 0 && t <= 0) t--;
      if (f <= t) {
        ll cf = ca * (x + b/d * f) + cb * (y - a/d * f);
        ll ct = ca * (x + b/d * t) + cb * (y - a/d * t);
        // cout << cf << " <> " << ct << endl;
        if (cf > ct) f = t;
        x = x + b/d * f;
        y = y - a/d * f;
        printf("%lld %lld\n", x, y);
      } else {
        printf("failed\n");
      }
    } else {
      printf("failed\n");
    }
  }
}

