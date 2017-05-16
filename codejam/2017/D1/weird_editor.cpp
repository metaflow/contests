#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif
#include <message.h>
#include "weird_editor.h"

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

const l MOD = e9 + 7;

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

tuple<l,l,l> collect(l from, l to, l d) {
  l c = 0;
  l r = 0;
  l last = -1;
  F(i, from, min(to, GetNumberLength())) {
    if (GetDigit(i) == d) {
      c++;
      r = (r * 10 + d) % MOD;
      last = i;
    }
  }
  return make_tuple(c, r, last);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l N = NumberOfNodes();
  bool master = MyNodeId() == 0;
  l answer = 0;
  l from = 0;
  l p = 0;
  if (master) {
    for (l d = 9; d > 0; d--) {
      l part = (GetNumberLength() - from);
      part = (part + N - 1) / N;
      F(i, 1, N) {
        PutLL(i, from + i * part);
        PutLL(i, from + (i + 1) * part);
        PutLL(i, d);
        Send(i);
      }
      vector<tuple<l,l,l>> v;
      v.emplace_back(collect(from + 0, from + part, d));
      F(i, 1, N) {
        Receive(i);
        l c = GetLL(i);
        l m = GetLL(i);
        l p = GetLL(i);
        v.emplace_back(make_tuple(c, m, p));
      }
      for (auto t : v) {
        l c = get<0>(t);
        l r = get<1>(t);
        l last = get<2>(t);
        if (c == 0) continue;
        p += c;
        answer = (answer * pow_mod(10, c, MOD) + r) % MOD;
        from = max(from, last + 1);
      }
    }
    p = GetNumberLength() - p; // zeroes
    answer = (answer * pow_mod(10, p, MOD)) % MOD;
    cout << answer << lf;
  } else {
    while(1) {
      Receive(0);
      l from = GetLL(0);
      l to = GetLL(0);
      l d = GetLL(0);
      auto t = collect(from, to, d);
      PutLL(0, get<0>(t));
      PutLL(0, get<1>(t));
      PutLL(0, get<2>(t));
      Send(0);
      if (d == 1) break;
    }
  }
}
