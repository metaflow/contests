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

vll __fibonacci_m_pow(vll &a, ll n, ll mod) {
  if (n == 1) return a;
  vll r(4), m1, m2;
  if (n % 2 == 0) {
    m1 = m2 = __fibonacci_m_pow(a, n / 2, mod);
  } else {
    m1 = a;
    m2 = __fibonacci_m_pow(a, n - 1, mod);
  }
  r[0] = (m1[0] * m2[0] + m1[1] * m2[2]) % mod;
  r[1] = (m1[0] * m2[1] + m1[1] * m2[3]) % mod;
  r[2] = (m1[2] * m2[0] + m1[3] * m2[2]) % mod;
  r[3] = (m1[2] * m2[1] + m1[3] * m2[3]) % mod;
  return r;
}

// n >= 1, {1, 1, 2, 3, 5, ...}
ll fibonacci(ll n, ll mod) {
  vll a(4);
  a[0] = 1; a[1] = 1; a[2] = 1; a[3] = 0;
  auto r = __fibonacci_m_pow(a, n, mod);
  return r[1];
}

ll pow2(ll n, ll m) {
  if (n == 0) return 1;
  if (n % 2 == 0) {
    ll t = pow2(n / 2, m);
    return (t * t) % m;
  }
  return (2 * pow2(n - 1, m)) % m;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  llu n, k, l, m;
  while (cin >> n >> k >> l >> m) {
    if (l < 64 && k >= (1ULL << l)) {
      cout << 0 << endl;
      continue;
    }
    ll zeroes = fibonacci(n + 2, m);
    ll ones = (pow2(n, m) - zeroes + m) % m;
    // cerr << zeroes << " 0" << endl;
    // cerr << ones << " 1" << endl;
    ll r = 1;
    for (llu i = 0; i < l; i++) {
     if (k & (1LL << i)) {
        r = (r * ones) % m;
     } else {
        r = (r * zeroes) % m;
     }
    }
    cout << (r % m) << endl;
  }
}


