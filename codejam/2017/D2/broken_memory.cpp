#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "broken_memory"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include "broken_memory.h"
#include "message.h"
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

const l MOD = e9 + 9;
const l m1 = e9 + 7;
const l m2 = e9 + 21;

l sign(l n) {
  if (n < 0) return -1;
  if (n == 0) return 0;
  return 1;
}

// conruent modulo, works for negative
l cong(l x, l mod) {
  return (x % mod + mod) % mod;
}

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

l divup(l a, l b) { // ceil div
  return (a + b - 1) / b;
}

// return gcd(a, b) and set x, y: a * x + b * y = gcd(a, b)
l extended_euclid(l a, l b, l& x, l& y) {
  if (b == 0) { x = 1; y = 0; return a; }
  l d = extended_euclid(b, a % b, x, y);
  l t = y;
  y = x - (a / b) * y;
  x = t;
  return d;
}

// return b: a * b = 1 (mod n)
l inverse_mod(l a, l n) {
  l x, y;
  l d = extended_euclid(a, n, x, y);
  if (d != 1) return 0;
  return cong(x, n);
}

// single combintions k from n
l nCr(l n, l k, l mod) {
  l a = 1;
  for (l i = n; i > n - k; i--) a = mult_mod(a, i, mod);
  l b = 1;
  F(i, 1, k + 1) b = mult_mod(b, i, mod);
  b = inverse_mod(b, mod);
  return mult_mod(a, b, mod);
}

// precompute all combinations up to (n n)
vvl combinations(l n, l mod) {
  vvl c(n + 1, vl(n + 1));
  F(i, 0, n) {
    c[i][0] = 1;
    F(j, 1, i + 1) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
    }
  }
  return c;
}

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator () (const std::pair<T1,T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);

    // Mainly for demonstration purposes, i.e. works but is overly simple
    // In the real world, use sth. like boost.hash_combine
    return h1 ^ h2;
  }
};

vl v;
vl p1, p2;
l id, nodes;
unordered_map<ll, ll, pair_hash> cache;
ll calc(l from, l to) {
  ll p = make_pair(from, to);
  assert(from < to);
  if (cache.count(p)) return cache[p];
  if (to - from == 1) {
    cache[p] = make_pair(v[from] % MOD, v[from] % MOD);
  } else {
    l mid = (to + from) / 2;
    ll a = calc(from, mid);
    ll b = calc(mid, to);
    cache[p] = make_pair(cong(a.first * p1[to - mid] + b.first, MOD),
                         cong(a.second * p2[to - mid] + b.second, MOD));
  }
  return cache[p];
}

vb answered;
bool answer(l x) {
  x = cong(x, nodes);
  if (answered[x]) return false;
  Receive(x);
  l from, to;
  from = GetLL(x);
  if (from == -1) {
    answered[x] = true;
    return false;
  }
  to = GetLL(x);
  l mid = (from + to) / 2;
  PutLL(x, calc(from, mid).first);
  PutLL(x, calc(from, mid).second);
  PutLL(x, calc(mid, to).first);
  PutLL(x, calc(mid, to).second);
  Send(x);
  return true;
}

void ask(l id, l from, l to) {
  PutLL(id, from);
  PutLL(id, to);
  Send(id);
}

ll GetP(l i) {
  l x = GetLL(i);
  l y = GetLL(i);
  return make_pair(x, y);
}

l dfs(l from, l to) {
  l a = (id + 1) % nodes;
  l b = (id + 2) % nodes;
  if (to - from == 1) {
    PutLL(a, -1);
    Send(a);
    PutLL(b, -1);
    Send(b);
    while (answer(id - 1) or answer(id - 2)) {};
    return from;
  }
  ask(a, from, to);
  ask(b, from, to);
  answer(id - 1);
  answer(id - 2);
  Receive(a);
  Receive(b);
  l mid = (from + to) / 2;
  ll v1 = calc(from, mid), v2 = calc(mid, to);
  ll a1 = GetP(a); ll a2 = GetP(a);
  ll b1 = GetP(b); ll b2 = GetP(b);
  if (id == 0 and 0) {
    cerr << from << ' ' << mid << ": " << v1.first << ' ' << a1.first << ' ' << b1.first << endl;
    cerr << mid << ' ' << to << ": " << v2.first << ' ' << a2.first << ' ' << b2.first << endl;
  }
  if (v1 == a1 or v1 == b1 or (a2 == b2 and v2 != a2)) {
    return dfs(mid, to);
  }
  return dfs(from, mid);
}

void solve(istream& cin, ostream& cout) {
  id = MyNodeId();
  nodes = NumberOfNodes();
  answered.resize(nodes);
  l n = GetLength();
  v.resize(n);
  p1.resize(n);
  p2.resize(n);
  p1[0] = 1;
  p2[0] = 1;
  F(i, 1, n) {
    p1[i] = (p1[i - 1] * m1) % MOD;
    p2[i] = (p2[i - 1] * m2) % MOD;
  }
  F(i, 0, n) v[i] = GetValue(i);
  calc(0, n);
  PutLL(0, dfs(0, n));
  Send(0);
  if (id != 0) return;
  F(i, 0, nodes) {
    if (i) cout << ' ';
    Receive(i);
    cout << GetLL(i);
  }
  cout << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
