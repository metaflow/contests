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

vl factorize_to_primes(vl& primes, l n) {
  vl factors;
  auto p = primes.begin();
  while (p != primes.end() && (*p) * (*p) <= n) {
    if (n % *p == 0) {
      factors.emplace_back(*p);
      while (n % *p == 0) n /= *p;
    }
    p++;
  }
  if (n != 1) factors.emplace_back(n);
  return factors;
}

l cost(vl& v, l p, l a, l b) {
  l sa = 0, sb = 0;
  l remove_from = 1;
  l total = 0;
  for (l i = 1; i < v.size(); i++) {
    sa += a;
    l x = v[i] % p;
    if ((x == 1) || (x == p - 1)) {
      sb += b;
    } else if (x != 0) {
      break;
    }
    if (sb <= sa) {
      total += sb;
      sb = 0; sa = 0; remove_from = i + 1;
    }
  }
  sa = 0; sb = 0;
  l remove_to = v.size() - 1;
  for (l i = v.size() - 1; i >= remove_from; i--) {
    sa += a;
    l x = v[i] % p;
    if ((x == 1) || (x == p - 1)) {
      sb += b;
    } else if (x != 0) {
      break;
    }
    if (sb <= sa) {
      total += sb;
      sb = 0; sa = 0; remove_to = i - 1;
    }
  }
  cerr << p << ": " << remove_from << ".." << remove_to << endl;
  if (remove_from <= remove_to) total += (remove_to - remove_from + 1) * a;
  return total;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, a, b;
  auto primes = sieve_primes();
  while (cin >> n >> a >> b) {
    vl v(n);
    l best_cost = (n - 1) * a;
    cerr << "---" << endl;
    for (l i = 0; i < n; i++) cin >> v[i];
    for (l j = -1; j <= 1; j++) {
      auto f = factorize_to_primes(primes, v[0] + j);
      for (auto p : f) {
        if (p == 1) continue;
        best_cost = min(best_cost, cost(v, p, a, b) + (j == 0 ? 0 : b));
      }
    }
    reverse(v.begin(), v.end());
    cerr << "---" << endl;
    for (l j = -1; j <= 1; j++) {
      auto f = factorize_to_primes(primes, v[0] + j);
      for (auto p : f) {
        if (p == 1) continue;
        best_cost = min(best_cost, cost(v, p, a, b) + (j == 0 ? 0 : b));
      }
    }
    cout << best_cost << endl;
  }
}
