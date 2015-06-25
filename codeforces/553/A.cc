#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

const ll MOD = 1000000007;
vll primes;
const ll MAX_PRIME = 1000;
vll sieve_primes() {
  bitset<MAX_PRIME + 1> b;
  vll primes;
  primes.emplace_back(2);
  for (ll i = 3; i <= MAX_PRIME; i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j <= MAX_PRIME; j += i) b.set(j);
  }
  return primes;
}

vll factorize_to_primes(vll& primes, ll n) {
  vll factors;
  auto p = primes.begin();
  while (p != primes.end() && (*p) * (*p) <= n) {
    while (n % *p == 0) {
      factors.emplace_back(*p);
      n /= *p;
    }
    p++;
  }
  if (n != 1) factors.emplace_back(n);
  return factors;
}

ll C(ll n, ll k) {
  ll r = 1;
  vll pn, pk;
  for (ll i = n - k + 1; i <= n; i++) {
    auto f = factorize_to_primes(primes, i);
    pn.insert(pn.end(), f.begin(), f.end());
  }
  for (ll i = 2; i <= k; i++) {
    auto f = factorize_to_primes(primes, i);
    pk.insert(pk.end(), f.begin(), f.end());
  }
  sort(pn.begin(), pn.end());
  sort(pk.begin(), pk.end());
  auto a = pn.begin();
  auto b = pk.begin();
  while (a != pn.end()) {
    while (b != pk.end() && (*a == *b)) { a++; b++; }
    if (a == pn.end()) break;
    r = (r * (*a)) % MOD;
    a++;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  primes = sieve_primes();
  ll k;
  while (cin >> k) {
    ll a = 1;
    ll total = 0;
    for (ll i = 0; i < k; i++) {
      ll b; cin >> b;
      a = (a * C(total + b - 1, b - 1)) % MOD;
      total += b;
    }
    cout << a << endl;
  }
}
