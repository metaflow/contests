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

const l MAX_PRIME = e7;
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

struct E {
  l value, permutation, length;
};

l get_permutation(l a) {
  vl v;
  while (a) {
    v.emplace_back(a % 10);
    a /= 10;
  }
  sort(v.begin(), v.end(), greater<l>());
  l result = 0;
  for (auto i : v) result = result * 10 + i;
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int i = {1, 2};
  cout << i << endl;
}
