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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

ll gcd(ll a, ll b) {
  while (b) {
    ll t = b;
    b = a % b;
    a = t;
  }
  return a;
}

ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}

ll n_len(ll a) {
  ll r = 0;
  while (a) {
    r++;
    a /= 10;
  }
  return r;
}

vi mask(ll a) {
  vi r(10);
  while (a) {
    r[a % 10]++;
    a /= 10;
  }
  return r;
}

int bit_count(ll a) {
  int r = 0;
  while (a) {
    if (a & 1) r++;
    a >>= 1;
  }
  return r;
}

const ll MAX_PRIME = 10000;
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

const int mult[] = {1, 10, 100, 1000, 10000};

int _at(int a, int p) {
  return (a / mult[p]) % 10;
}

int _rm(int a, int p) {
  return (a / mult[p + 1]) + (a % mult[p]);
}

bool reducible(const int to_remove, const int u, const int d, const int p_u, const int a, const int b, const int n) {
  if (to_remove == 0) {
    if (u * d == 0) return false;
    ll g = gcd(u, d);
    return (u / g == a && d / g == b);
  }
  for (ll i = p_u; i < n; i++) {
    int y = _at(u, i);
    if (y == 0) continue;
    for (ll j = 0; j < n; j++) {
      if (_at(d, j) != y) continue;
      if (reducible(to_remove - 1, _rm(u, i), _rm(d, j), i, a, b, n - 1)) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto primes = sieve_primes();
  ll n, k;
  cin >> n >> k;
  ll L = n - k;
  ll u = 0, d = 0;
  ll m = mult[n - 1];
  for (ll i = m; i < m * 10; i++) {
    for (ll j = i + 1; j < m * 10; j++) {
      ll g = gcd(i, j);
      ll a = i / g, b = j / g;
      if (n_len(j / g) > L) continue;
      u++;
      // auto mi = mask(i);
      // auto mj = mask(j);
      // for (ll q = r)
    }
  }
  cout << u << " " << d << endl;
}
