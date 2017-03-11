#include <bits/stdc++.h>

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
const l e0 = 1, e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;
#define ALL(x) begin(x), end(x)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

// (a * b) % mod, safe for l near max
l mult_mod(l a, l b, l mod) {
  l x = 0;
  while (b) {
    if (b % 2) x = (x + a) % mod;
    a = (a * 2) % mod;
    b /= 2;
  }
  return x;
}

// (base^power) % mod, safe for l near max
l pow_mod(l base, l power, l mod) {
  l r = 1;
  while (power) {
    if (power % 2) r = mult_mod(r, base, mod);
    base = mult_mod(base, base, mod);
    power /= 2;
  }
  return r;
}

vl __fibonacci_m_pow(vl &a, l n, l mod) {
  if (n == 1) return a;
  vl r(4), m1, m2;
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
l fibonacci(l n, l mod) {
  vl a(4);
  a[0] = 1; a[1] = 1; a[2] = 1; a[3] = 0;
  auto r = __fibonacci_m_pow(a, n, mod);
  return r[1];
}

void grow(l a, l b, l& c, l& sum, l t, l m) {
  l t3 = pow_mod(3, t, 2 * m);
  sum = (mult_mod(sum - a - c + 2 * m, t3, 2 * m) +
         mult_mod(a + c, (t3 + 1) / 2, 2 * m)) % m;
  if (t > 0) {
    c = (mult_mod(c, fibonacci(t + 1, m), m) +
         mult_mod(b, fibonacci(t, m), m)) % m;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, x, y, mod;
  while (cin >> n >> x >> y >> mod) {
    vl v(n);
    for (l i = 0; i < n; i++) cin >> v[i];
    l a = v[0];
    if (n == 1) {
      cout << (a % mod) << '\n';
      continue;
    }
    l b = v[n - 2];
    l c = v[n - 1];
    l sum = accumulate(ALL(v), (l)0) % mod;
    grow(a, b, c, sum, x, mod);
    grow(a, b, c, sum, y, mod);
    cout << sum << '\n';
  }
}
