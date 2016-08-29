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

const ll MAX_PRIME = 1100;
bitset<MAX_PRIME + 1> b;

vll sieve_primes() {
  vll primes;
  primes.emplace_back(2);
  for (ll i = 2; i <= MAX_PRIME; i ++) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j <= MAX_PRIME; j += i) b.set(j);
  }
  return primes;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto primes = sieve_primes();
  b[0] = true;
  string s;
  while (cin >> s) {
    ll v = 0;
    for (auto c : s) {
      if ('a' <= c && c <= 'z') {
        v += c - 'a' + 1;
        continue;
      }
      if ('A' <= c && c <= 'Z') {
        v += c - 'A' + 27;
        continue;
      }
    }
    // cout << v << endl;
    if (b[v]) {
      cout << "It is not a prime word." << endl;
    } else {
      cout << "It is a prime word." << endl;
    }
  }
}
