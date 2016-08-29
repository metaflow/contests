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
  primes.emplace_back(2);
  for (ll i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < b.size(); j += i) b.set(j);
  }
}

vi factorize(ll n) {
  vi r;
  auto i = primes.begin();
  while (i != primes.end() && (*i)*(*i) <= n) {
    while (n % *i == 0) {
      r.emplace_back(*i);
      n /= *i;
    }
    i++;
  }
  if (n != 1) r.emplace_back(n);
  return r;
}
int main() {
  sieve();
  ll n;
  while (cin >> n, n) {
    auto r = factorize(abs(n));
    printf("%lld = ", n);
    if (n < 0) printf("-1 x ");
    auto i = r.begin();
    while (true) {
      printf("%d", *i);
      i++;
      if (i == r.end()) break;
      printf(" x ");
    }
    printf("\n");
  }
}
