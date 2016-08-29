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

vector<ii> factorize(ll n) {
  vector<ii> r;
  auto i = primes.begin();
  while (i != primes.end() && (*i)*(*i) <= n) {
    int c = 0;
    while (n % (*i) == 0) {
      n /= *i;
      c++;
    }
    if (c) r.emplace_back(*i, c);
    i++;
  }
  if (n != 1) r.emplace_back(n, 1);
  return r;
}

int main() {
  sieve();
  ll n, m;
  while (cin >> n >> m) {
    auto r = factorize(m);
    bool ok = true;
    for (auto p = r.begin(); p != r.end(); p++) {
      ll t = n;
      int c = 0;
      while (t) {
        t = t / p->first;
        c += t;
      }
      ok = ok && (c >= p->second);
    }
    if (ok) {
      printf("%lld divides %lld!\n", m, n);
    } else {
      printf("%lld does not divide %lld!\n", m, n);
    }
  }
}
