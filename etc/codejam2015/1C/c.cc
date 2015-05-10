#include <unistd.h>
#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();

ll C, D, V;
vll coins;

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    cin >> C >> D >> V;
    coins.resize(D);
    for (int i = 0; i < D; i++) cin >> coins[i];
    ll s = 0;
    for (ll c : coins) s += C * c;
    int ans = 0;
    int p = D - 1;
    while (V) {
      ll t = coins[p];
      if (V > s) {
        // printf("shortage %lld - %lld = %lld\n", V, s, V - s);
        // usleep(5000);
        ans++;
        ll x = (V - s) / C;
        while (x * C < (V - s)) x++;
        auto u = lower_bound(coins.begin(), coins.end(), x);
        while (u != coins.end() && x == *u) { x++; u++; }
        coins.emplace_back(x);
        // printf("add %lld\n", x);
        sort(coins.begin(), coins.end());
        p++;
        s += x * C;
        continue;
      }
      V = max(t - 1, V - t * C);
      s -= t * C;
      p--;
    }
    printf("Case #%d: %d\n", tc, ans);
  }
}
