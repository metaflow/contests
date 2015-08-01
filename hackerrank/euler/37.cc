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
bitset<MAX_PRIME + 1> b;

bool is_prime(ll a) {
  return !b[a];
}
vll sieve_primes() {
  vll primes;
  b[1] = true;
  for (ll i = 2; i <= MAX_PRIME; i ++) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j <= MAX_PRIME; j += i) b.set(j);
  }
  return primes;
}

vll filter_truncatable(vll& primes) {
  vll T;
  for (auto p : primes) {
    if (p < 10) continue;
    auto t = p;
    bool ok = true;
    ll k = 1;
    while (t > 10) {
      t /= 10;
      k *= 10;
      if (!is_prime(t)) { ok = false; break; }
    }
    t = p;
    while (t > 10) {
      t = t % k;
      k /= 10;
      if (!is_prime(t)) { ok = false; break; }
    }
    if (ok) T.emplace_back(p);
  }
  return T;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto primes = sieve_primes();
  auto T = filter_truncatable(primes);
  ll n; cin >> n;
  ll answer = 0;
  for (auto i : T) {
    if (i >= n) break;
    answer += i;
  }
  cout << answer << endl;
}
