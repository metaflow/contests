
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
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
#define ALL(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

const l MAX_PRIME = 50000;
// returns vector of v[i] = `biggest prime divisor of i`
vl sieve_primes(vl& primes) {
  vl next_div(MAX_PRIME, 1);
  for (l i = 2; i < MAX_PRIME; i++) {
    if (next_div[i] != 1) continue;
    primes.emplace_back(i);
    for (l j = i; j < MAX_PRIME; j += i) next_div[j] = i;
  }
  return next_div;
}

// not sorted
vl factorize_to_primes(l n, vl& primes, vl& next_div) {
  auto p = primes.begin();
  vl result;
  while (n >= MAX_PRIME and p != primes.end()) {
    while (n % *p == 0) { result.emplace_back(*p); n /= *p; }
    p++;
  }
  if (n >= MAX_PRIME) {
    result.emplace_back(n);
    n = 1;
  }
  while (n != 1) {
    result.emplace_back(next_div[n]);
    n /= next_div[n];
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vl primes;
  auto next_div = sieve_primes(primes);
  l n;
  while (cin >> n, n) {
    auto r = factorize(abs(n), primes, next_div);
    sort(ALL(r));
    cout << n << " = ";
    if (n < 0) cout << "-1 x ";
    auto i = r.begin();
    while (true) {
      cout << *i;
      i++;
      if (i == r.end()) break;
      cout << " x ";
    }
    cout << '\n';
  }
}
