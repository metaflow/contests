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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

ll gcd(ll a, ll b) {
  while (b) {
    ll t = b;
    b = a % b;
    a = t;
  }
  return a;
}

ll lcm(ll a, ll b) {
  return a * b / gcd(a, b);
}

ll n_len(ll a) {
  ll r = 0;
  while (a) {
    r++;
    a /= 10;
  }
  return r;
}

vi mask(ll a) {
  vi r(10);
  while (a) {
    r[a % 10]++;
    a /= 10;
  }
  return r;
}

int bit_count(ll a) {
  int r = 0;
  while (a) {
    if (a & 1) r++;
    a >>= 1;
  }
  return r;
}

const ll MAX_PRIME = 10000;
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

const int mult[] = {1, 10, 100, 1000, 10000};

int _at(int a, int p) {
  return (a / mult[p]) % 10;
}

int _rm(int a, int p) {
  return (a / mult[p + 1]) * mult[p] + (a % mult[p]);
}

const int MAX = 10000;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vector<vector<set<int>>> reducible(MAX);
  for (ll i = 0; i < MAX; i++) reducible[i].resize(4);

  for (ll i = MAX - 1; i >= 10; i--) {
    for (int p = 0; p < 4; p++) {
      if (_at(i, p) == 0) continue;
      int to = _rm(i, p);
      reducible[to][1].insert(i);
      for (ll j = 1; j < 3; j++) {
        reducible[to][j + 1].insert(
          reducible[i][j].begin(),
          reducible[i][j].end());
      }
    }
  }

  ll n, k;
  while (cin >> n >> k) {
    ll L = n - k;
    ll from = mult[n - 1], to = mult[n];
    set<ii> answer;
    for (ll i = 1; i < mult[L]; i++) {
      auto mi = mask(i);
      for (ll j = i + 1; j < mult[L]; j++) {
        auto l = reducible[j][k].lower_bound(from);
        auto t = reducible[j][k].upper_bound(to);
        auto mj = mask(j);
        for (auto d = l; d != t; d++) {
          int c = i * (*d);
          if (c % j != 0) continue;
          c /= j;
          if (n_len(c) != n) continue;
          if (reducible[i][k].count(c) == 0) continue;
          auto md = mask(*d);
          auto mc = mask(c);
          bool matched = true;
          for (int p = 1; p < 10; p++) {
            int dc = mc[p] - mi[p];
            matched = matched && (dc == md[p] - mj[p]);
          }
          if (matched) answer.emplace(c, *d);
        }
      }
    }
    ll sum_n = 0, sum_d = 0;
    for (auto p : answer) {
      sum_n += p.first;
      sum_d += p.second;
    }
    cout << sum_n << ' ' << sum_d << endl;
  }
}
