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

const ll MAX_PRIME = 100;
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

bitset<101> primes;

void dfs(int s, int n, ll m, int f, vi& q) {
  if (n == 0) {
    if (s == 0) {
      for (size_t i = 0; i < q.size(); i++) {
        if (i) cout << " ";
        cout << q[i];
      }
      cout << endl;
    }
    return;
  }
  q.emplace_back(0);
  for (ll i = f; i <= s; i++) {
    if (gcd(i, m) > 1) continue;
    q.back() = i;
    dfs(s - i, n - 1, lcm(m, i), (i == 1 ? 1 : i + 1), q);
  }
  q.pop_back();
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  auto p = sieve_primes();
  for (auto a : p) primes.set(a);
  primes.set(1);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    cout << "Case " << tc << ":" << endl;
    int s, t;
    cin >> s >> t;
    vi q;
    dfs(s, t, 1, 1, q);
  }
}
