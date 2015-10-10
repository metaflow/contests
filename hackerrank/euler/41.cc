#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
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

bool is_prime(l t, vl& primes) {
  if (t == 1) return false;
  for (auto i : primes) {
    if (t < i * i) return true;
    if (t % i == 0) return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto p = sieve_primes();
  vl pandigital;
  for (l i = 4; i <= 10; i+=3) {
    vl d(i);
    for (l j = 1; j <= i; j++) d[j - 1] = j % 10;
    while (true) {
      l t = 0;
      for (l j = 0; j < i; j++) t = t * 10 + d[j];
      if (is_prime(t, p)) pandigital.emplace_back(t);
      if (!next_permutation(d.begin(), d.end())) break;
    }
  }
  sort(pandigital.begin(), pandigital.end());
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    l n; cin >> n;
    auto p = upper_bound(pandigital.begin(), pandigital.end(), n);
    if (p == pandigital.begin()) {
      cout << -1 << endl;
    } else {
      cout << *(p - 1) << endl;
    }
  }
}
