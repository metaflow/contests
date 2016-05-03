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

struct Result {
  l value;
  vl divisors;
};

vl primes;

const l MAX_PRIME = 1000000;
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

vl factorize_to_primes(l n) {
  vl factors;
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

l get_devisor(l x) {
  auto factors = factorize_to_primes(x);
  assert(factors.size());
  if (factors[0] != x) return factors[0];
  return 0;
}

l as_base(l n, l base) {
  l m = 1;
  l x = 0;
  while (n) {
    if (n & 1) x += m;
    n >>= 1;
    m *= base;
  }
  return x;
}

Result get_result(l x) {
  Result r;
  r.value = x;
  for (l base = 2; base < 11; base++) {
    l y = as_base(x, base);
    l divisor = get_devisor(y);
    if (!divisor) break;
    r.divisors.emplace_back(divisor);
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  primes = sieve_primes();
  l tcc; cin >> tcc; // ignore
  l n, j; cin >> n >> j;
  l m = 1 + (1L << (n - 1));
  cout << m << endl;
  vector<Result> results;
  for (l i = 0; results.size() < j && i < 1000; i++) {
    l x = m + (i << 1);
    auto r = get_result(x);
    if (r.divisors.size() == 9) {
      results.emplace_back(r);
    }
  }
  cout << "Case #1:" << endl;
  for (auto r : results) {
    cout << as_base(r.value, 10);
    for (auto d : r.divisors) cout << " " << d;
    cout << endl;
  }
}
