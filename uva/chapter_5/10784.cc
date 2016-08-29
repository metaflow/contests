#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

ll d(ll n) { return n * (n - 3) / 2; }

int main() {
  int tc = 0;
  ll k;
  while (cin >> k, k) {
    tc++;
    ll n = (ll)((3 + sqrt(9 + 8 * k)) / 2);
    while (d(n) < k) n++;
    n = max(n, (ll)4);
    printf("Case %d: %lld\n", tc, n);
  }
}
