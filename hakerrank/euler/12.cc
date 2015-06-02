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

vector<ii> factorize_to_primes(vll& primes, ll n) {
  vector<ii> factors;
  auto p = primes.begin();
  while (p != primes.end() && (*p) * (*p) <= n) {
    int c = 0;
    while (n % *p == 0) {
      c++;
      n /= *p;
    }
    if (c) factors.emplace_back(*p, c);
    p++;
  }
  if (n != 1) factors.emplace_back(n, 1);
  return factors;
}

const int MAX = 1100;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll sum = 0;
  auto primes = sieve_primes();
  vll mins(MAX + 2);
  ll m = 0;
  for (int i = 1; i < 42000; i++) {
    sum += i;
    auto f = factorize_to_primes(primes, sum);
    ll k = 1;
    for (auto p : f) k *= p.second + 1;
    m = max(m, k);
    if (k > MAX + 1 || mins[k] != 0) continue;
    mins[k] = sum;
  }

  for (int i = MAX - 1; i > 0; i--) {
    if (mins[i] == 0 ||
        (mins[i] > mins[i + 1] && mins[i + 1] != 0))
      mins[i] = mins[i + 1];
  }

  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    cout << mins[n + 1] << endl;
  }
}
