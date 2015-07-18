#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();

const ll MAX_PRIME = 6000000;
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

int main() {
  ll n;
  cin >> n;
  auto primes = sieve_primes();
  ll best_a, best_b, best = 0;
  for (auto b : primes) {
    if (b > n) break;
    // 1 + a + b is prime = p | a <= n
    for (auto p : primes) {
      ll a = p - b - 1;
      if (abs(a) > n) break;
      ll i = 2;
      while (true) {
        ll m = i * i + a * i + b;
        if (m <= 0 || !binary_search(primes.begin(), primes.end(), m)) break;
        i++;
      }
      if (best < i) {
        best_a = a;
        best_b = b;
        best = i;
      }
    }
  }
  cout << best_a << " " << best_b << endl;
}
