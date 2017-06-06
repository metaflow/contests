#if defined(LOCAL)
#define PROBLEM_NAME "C"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
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

const l MOD1 = e9 + 9;
const l MOD2 = 17;
const l MOD3 = 31;

l add(l h, l x, l a, l b) {
  return cong(h * a + x, b);
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
}; // TODO

void solve(istream& cin, ostream& cout) {
  l N;
  while (cin >> N) {
    vl v(N);
    F(i, 0, N) {
      cin >> v[i];
    }
    vl pows1(N), pows2(N);
    pows1[0] = 1;
    pows2[0] = 1;
    F(i, 1, N) {
      pows1[i] = cong(pows1[i - 1] * MOD2, MOD1);
      pows2[i] = cong(pows2[i - 1] * MOD3, MOD1);
    }
    bool eq = true;
    F(i, 1, N) eq = eq and (v[i - 1] == v[i]);
    if (eq) {
      cout << 0 << lf;
      continue;
    }
    l answer = N;
    F(w, 1, N) {
      l h1 = 0, h2 = 0;
      F(i, 0, w - 1) {
        h1 = cong(h1 * MOD2 + v[i], MOD1);
        h2 = cong(h2 * MOD3 + v[i], MOD1);
      }
      unordered_map<ll, l, pair_hash> uniq;
      bool ok = true;
      F(i, w - 1, N - 1) {
        h1 = cong(h1 * MOD2 + v[i], MOD1);
        h2 = cong(h2 * MOD3 + v[i], MOD1);
        auto p = make_pair(h1, h2);
        if (uniq.count(p)) {
          if (uniq[p] != v[i + 1]) {
            ok = false;
            break;
          }
        } else {
          uniq[p] = v[i + 1];
        }
        h1 = cong(h1 - pows1[w - 1] * v[i - w + 1], MOD1);
        h2 = cong(h2 - pows2[w - 1] * v[i - w + 1], MOD1);
      }
      if (ok) {
        answer = w;
        break;
      }
    }
    cout << answer << lf;
  }
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
