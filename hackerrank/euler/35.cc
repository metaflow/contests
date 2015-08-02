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

const ll MAX_PRIME = 1000000;
bitset<MAX_PRIME + 1> b;

vll sieve_primes() {
  vll primes;
  for (ll i = 2; i <= MAX_PRIME; i++) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j <= MAX_PRIME; j += i) b.set(j);
  }
  return primes;
}

ll rotate(ll a) {
  ll b = 0;
  while (a) {
    b *= 10;
    b += a % 10;
    a /= 10;
  }
  return b;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto primes = sieve_primes();
  vll circular;
  ll m = 1;
  for (auto p : primes) {
    ll t = p;
    while (m * 10 < t) m *= 10;
    bool ok = true;
    while (true) {
      ll q = t / m;
      t %= m;
      t = t * 10 + q;
      if (t == p) break;
      if (b[t]) ok = false;
    }
    if (ok) circular.emplace_back(p);
  }
  ll n; cin >> n;
  auto u = lower_bound(circular.begin(), circular.end(), n);
  cout << accumulate(circular.begin(), u, 0) << endl;
}
