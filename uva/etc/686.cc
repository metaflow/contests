#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using vll = vector<ll>;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vll primes;
const int MAX = (1 << 15) + 100;

void sieve() {
  bitset<MAX> b;
  primes.emplace_back(2);
  for (ll i = 3; i < MAX; i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < MAX; j += i) b.set(j);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  sieve();
  ll n;
  while (cin >> n, n) {
    auto a = primes.begin();
    auto b = upper_bound(primes.begin(), primes.end(), n - *a);
    ll count = 0;
    while (true) {
      while (*a + *b > n) b--;
      if (a > b) break;
      if (*b == t) count++;
      a++;
      if (a > b) break;
    }
    cout << count << endl;
  }
}
