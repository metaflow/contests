#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

const l MAX = 2 * e6;

const l MAX_PRIME = MAX;
vl sieve_primes() {
  bitset<MAX_PRIME + 1> b;
  vl primes;
  primes.emplace_back(2);
  for (l i = 3; i <= MAX_PRIME; i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (l j = i * i; j <= MAX_PRIME; j += i) b.set(j);
  }
  return primes;
}

vl factorize_to_primes(vl& primes, l n) {
  vl factors;
  auto p = primes.begin();
  while (p != primes.end() && (*p) * (*p) <= n) {
    if (n % *p == 0) {
      factors.emplace_back(*p);
    }
    while (n % *p == 0) n /= *p;
    p++;
  }
  if (n != 1) factors.emplace_back(n);
  return factors;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto primes = sieve_primes();
  l n, k;
  while (cin >> n >> k) {
    l streak = 0;
    for (l i = 2; i <= n + k - 1; i++) {
      auto factors = factorize_to_primes(primes, i);
      if (factors.size() == k) {
        streak++;
        if (streak == k) {
          cout << (i - k + 1) << endl;
          streak--;
        }
      } else {
        streak = 0;
      }
    }
  }
}
