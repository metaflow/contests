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

const ll MAX = 1000000000000;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto primes = sieve_primes();
  vll v;
  for (auto p : primes) {
    ll t = p * p;
    while (t < MAX) {
      v.emplace_back(t);
      t *= p;
    }
  }
  sort(v.begin(), v.end());
  int n; cin >> n;
  while (n--) {
    ll a, b; cin >> a >> b;
    auto pa = lower_bound(v.begin(), v.end(), a);
    auto pb = upper_bound(v.begin(), v.end(), b);
    // if (*pb > b) pb--;
    cout << (pb - pa) << endl;
  }
}
