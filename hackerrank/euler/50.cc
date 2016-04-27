#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

const l MAX_PRIME = 6000000;
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

bool is_prime(vl& primes, l n) {
  auto p = primes.begin();
  while (p != primes.end() && (*p) * (*p) <= n) {
    if (n % *p == 0) return (n == *p);
    p++;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vl primes = sieve_primes();
  vl sum(primes.size() + 1);
  l m = 0;
  l non_primes = 0, small_non_primes = 0, matches = 0;
  for (l i = 1; i < sum.size(); i++) sum[i] = sum[i - 1] + primes[i - 1];
  cout << sum[22] << endl;
  l T; cin >> T;
  while (T--) {
    l n; cin >> n;
    auto p = lower_bound(sum.begin(), sum.end(), n);
    if (*p > n) p--;
    while (!is_prime(primes, *p)) p--;
    cout << *p << " " << std::distance(sum.begin(), p) << endl;
  }
}
