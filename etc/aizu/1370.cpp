#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

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

const l MAX_PRIME = e6;
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

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}

vl get_hash_primes(l k) {
  const l e9_primes[] = {
    7, 9, 21, 33, 87, 93, 97, 103, 123, 181, 207, 223, 241, 271, 289, 297, 321,
    349, 363, 403, 409, 411, 427, 433, 439, 447, 453, 459, 483, 513, 531, 579, 607,
    613, 637, 663, 711, 753, 787, 801, 829, 861, 871, 891, 901, 919, 931, 933, 993 };
  vl t; for (auto i : e9_primes) t.emplace_back(e9 + i);
  shuffle(all(t), source);
  if (t.size() > k) t.resize(k);
  return t;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // vl primes;
  // auto d = sieve_primes(primes);
  // F(i, e9, e9 + 1000) if (factorize_to_primes(i, primes, d).size() == 1) {
  //   cout << i - e9 << lf;
  // }
  l h = 10;
  auto hh = get_hash_primes(h);
  l A = 4000;
  l positions = 26;
  vvl pows(h, vl(positions));
  F(i, 0, h) {
    pows[i][0] = 1;
    F(j, 1, positions) pows[i][j] = (pows[i][j - 1] * A) % hh[i];
  }
  string s1, s2;
  vl hs(h);
  F(i, 0, h) hs[i] = random_in_range(0, e9);
  while (cin >> s1 >> s2) {
    vector<bool> bloom(e9);
    vvl v1(h, vl(s1.size()));
    F(i, 0, s1.size()) {
      F(k, 0, h) v1[k][i] = pows[k][s1[i] - 'a'];
    }
    vvl v2(h, vl(s2.size()));
    F(i, 0, s2.size()) {
      F(k, 0, h) v2[k][i] = pows[k][s2[i] - 'a'];
    }
    F(i, 0, s1.size()) {
      vl v = hs;
      F(j, i, s1.size()) {
        F(k, 0, h) {
          v[k] = (v[k] + v1[k][j]) % hh[k];
          bloom[v[k]] = true;
        }
      }
    }
    l answer = 0;
    F(i, 0, s2.size()) {
      vl v = hs;
      F(j, i, s2.size()) {
        F(k, 0, h) {
          v[k] = (v[k] + v2[k][j]) % hh[k];
        }
        bool f = true;
        F(k, 0, h) f = f and bloom[v[k]];
        if (f) answer = max(answer, j - i + 1);
      }
    }
    cout << answer << lf;
  }
}
