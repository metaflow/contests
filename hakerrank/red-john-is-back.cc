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

const ll MAX_PRIME = 250000;
vll sieve_primes() {
  bitset<MAX_PRIME + 1> b;
  vll primes;
  primes.emplace_back(2);
  for (ll i = 3; i < MAX_PRIME; i += 2) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < MAX_PRIME; j += i) b.set(j);
  }
  return primes;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc;
  cin >> tcc;
  vll ways(41);
  for (int i = 0; i < 41; i++) {
    if (i < 4) {
      ways[i] = 1;
    } else {
      ways[i] = ways[i - 1] + ways[i - 4];
    }
  }
  auto primes = sieve_primes();
  // cerr << primes.size() << " " << primes.back() << endl;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    auto a = upper_bound(primes.begin(), primes.end(), ways[n]);
    ll answer = a - primes.begin();
    // cout << ways[n] << endl;
    cout << answer << endl;
  }
}
