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

ll brute(ll n) {
  set<ll> s;
  for (ll i = 2; i <= n; i++) {
    ll a = i;
    for (ll j = 2; j <= n; j++) {
      a *= i;
      s.insert(a);
    }
  }
  return s.size();
}

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

const int MAX = 100001;

ll f(ll n) {
  ll a = (n - 1) * (n - 1);
  bitset<MAX> b;
  auto primes = sieve_primes();
  for (ll i = 2; i <= n; i++) {
    if (b[i]) continue;
    ll k = 2, t = i * i;
    while (t <= n) {
      b.set(t);
      vector<bool> g(n);
      for (ll j = 1; j < k; j++) {
        ll y = lcm(j, k);
        for (ll h = y; h <= n * j; h += y) {
          if (g[h / k] || (h / k <= 1)) continue;
          g[h / k] = true;
          a--;
        }
        // if (j == 1 && y != k) a++;
        // cout << (n * j / y) << " " << y << " " << i << " " << t << " " << j  << endl;
        // cerr << (n / k - 1) << " " << t << " " << i << endl;
      }
      k++;
      t *= i;
    }
  }
  return a;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  cin >> n;
  // for (int n = 2; n < 17; n++) {
  //   cout << n << " " << f(n) << " " << brute(n) << endl;
  // }
  cout << f(n) << endl;
}
