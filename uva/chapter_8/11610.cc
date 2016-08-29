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

// RSQ for range [1, n]
struct fenwik_tree {
  vll tree;
  ll max_p;
  fenwik_tree(size_t n) {
    max_p = n;
    tree.resize(n + 1);
  };
  // sum of [1, p], O(log(max))
  ll read(ll p) {
    ll sum = 0;
    while (p) {
      sum += tree[p];
      p -= (p & -p);
    }
    return sum;
  }
  // O(log(max))
  void add(ll p, ll value) {
    while (p <= max_p) {
      tree[p] += value;
      p += (p & -p);
    }
  }
  // find lowest index with given sum, -1 if not found O(log(max))
  ll find(ll sum) {
    ll mask = max_p;
    while (true) {
      ll lower = (mask & -mask);
      if (lower == mask) break;
      mask -= lower;
    }
    ll p = 0;
    ll top = -1;
    while (mask != 0) {
      ll m = p + mask;
      if (m <= max_p) {
        if (sum == tree[m]) top = m;
        if (sum > tree[m]) {
          p = m;
          sum -= tree[m];
        }
      }
      mask >>= 1;
    }
    if (sum != 0) return top;
    return p;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto primes = sieve_primes();
  vll reverse;
  for (auto i : primes) {
    ll r = 0;
    while (i) {
      r *= 10;
      r += i % 10;
      i /= 10;
    }
    while (r < 1000000) r *= 10;
    assert(r < 10000000);
    reverse.emplace_back(r);
  }
  sort(reverse.begin(), reverse.end());
  fenwik_tree f(reverse.size());
  vll number_of_factors(reverse.size());
  for (size_t i = 0; i < reverse.size(); i++) {
    number_of_factors[i] = factorize_to_primes(primes, reverse[i]).size();
    f.add(i + 1, number_of_factors[i]);
  }
  fenwik_tree shift(reverse.size());
  for (size_t i = 0; i < reverse.size(); i++) shift.add(i + 1, 1);
  char op; ll a;
  while (cin >> op >> a) {
    switch (op) {
      case 'q': cout << f.read(shift.find(a + 1)) << endl; break;
      case 'd':
        auto p = lower_bound(reverse.begin(), reverse.end(), a);
        auto i = p - reverse.begin() + 1;
        f.add(i, -number_of_factors[i - 1]);
        shift.add(i, -1);
        break;
    }
  }
}
