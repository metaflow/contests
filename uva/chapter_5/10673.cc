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
    x = 1; y = 0; d = a; return;
  }
  euclid(b, a % b);
  ll t = x;
  x = y;
  y = t - a / b * y;
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    ll n, k;
    cin >> n >> k;
    ll a = n / k;
    ll b = a;
    if (n % k != 0) b++;
    if (a == b) {
      printf("%lld 0\n", k);
    } else {
      euclid(a, b);
      x *= n / d;
      y *= n / d;
      ll t = (x + y) / (a - b) * d;
      printf("%lld %lld\n", (x + b / d * t), (y - a / d * t));
    }
  }
}
