#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vector<ll> primes;

void sieve() {
  bitset<50000> b;
  b.reset();
  primes.emplace_back(2);
  for (ll i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < b.size(); j += i) b.set(i);
  }
}

vector<ii> as_primes(int n) {
  auto p = primes.begin();
  vector<ii> result;
  while (p != primes.end() && (*p)*(*p) <= n) {
    if (n % (*p) == 0) {
      int c = 0;
      while (n % (*p) == 0) {
        c++;
        n /= *p;
      }
      result.emplace_back(*p, c);
    }
    p++;
  }
  if (n != 1) result.emplace_back(n, 1);
  return result;
}

int main() {
  sieve();
  int n;
  while (cin >> n, n) {
    auto p = as_primes(n);
    ll r = 1;
    for (auto e : p) r *= (e.second * 2 + 1);
    r = (r + 1) / 2;
    printf("%d %lld\n", n, r);
  }
}
