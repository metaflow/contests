#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  ll n;
  while (cin >> n) {
    ll a = floor(pow(2 * n, 0.5));
    while (a * (a + 1) / 2 + 1 <= n) a++;
    printf("TERM %lld IS ", n);
    ll t = n - (a * (a - 1) / 2 + 1);
    if (a % 2 == 0) {
      printf("%lld/%lld\n", (1 + t), (a - t));
    } else {
      printf("%lld/%lld\n", (a - t), (1 + t));
    }
  }
}
