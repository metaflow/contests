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

const ll MAX_PRIME = 2000000;
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

bool is_palindrome(ll a) {
  ll k = 1;
  while (k * 10 < a) k *= 10;
  while (a) {
    if (a / k != a % 10) return false;
    a %= k;
    a /= 10;
    k = k / 100;
  }
  return true;
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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto primes = sieve_primes();
  ll answer = 0;
  ll q, w;
  while (cin >> q >> w) {
    ll a = 0, b = 0;
    auto p = primes.begin();
    for (ll i = 1; i < 2000000; i++) {
      if (i == *p) {
        a++;
        p++;
      }
      if (is_palindrome(i)) b++;
      ll c = a; ll d = b;
      if (c != 0) {
        c /= gcd(a, b);
        d /= gcd(a, b);
      }
      if (q * b >= w * a) answer = i;
    }
    cout << answer << endl;
  }
}
