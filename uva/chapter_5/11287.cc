#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

vector<ll> primes;

ll pow_mod(ll base, ll pow, ll mod) {
  if (pow == 0) return 1;
  if (pow % 2 == 0) {
    ll t = pow_mod(base, pow / 2, mod);
    return (t * t) % mod;
  }
  return (base * pow_mod(base, pow - 1, mod)) % mod;
}

void sieve() {
  bitset<40000> b;
  primes.emplace_back(2);
  for (ll i = 3; i < b.size(); i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < b.size(); j += i) b.set(j);
  }
}

bool prime(ll n) {
  auto p = primes.begin();
  while (p != primes.end() && ((*p)*(*p) <= n)) {
    if (n % *p == 0) return false;
    p++;
  }
  return n != 1;
}

int main() {
  sieve();
  ll p, a;
  while (cin >> p >> a, p + a != 0) {
    if (pow_mod(a, p, p) == (a % p) && !prime(p)) {
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }
}
