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
  if ((l)t.size() > k) t.resize(k);
  return t;
}

l gcd(l a, l b) {
  while (b) { l t = b; b = a % b; a = t; }
  return a;
}

l lcm(l a, l b) { return a * b / gcd(a, b); }

l A = 27;

namespace std {
template <>
struct hash<tuple<l,l,l>> {
  std::size_t operator()(const tuple<l,l,l>& k) const {
    return get<0>(k) ^ get<1>(k) ^ get<2>(k);
  }
};
}

// TODO: cong
l mod(l x, l mod) {
  return (x % mod + mod) % mod;
}

void add(vvl& v, vvl& pows, vl& hh,
         unordered_map<tuple<l,l,l>, l>& freq, l dx, l dy, l size) {
  l n = v.size();
  l m = v[0].size();
  l h = hh.size();
  vvb visited(n, vb(m));
  F(r, 0, n) F(c, 0, m) {
    if (visited[r][c]) continue;
    vl full_hash(h), tail(h);
    l w = 0;
    l x = r, y = c;
    while (not visited[x][y]) {
      w++;
      visited[x][y] = true;
      F(k, 0, h) full_hash[k] = mod(full_hash[k] * A + v[x][y], hh[k]);
      x = mod(x + dx, n);
      y = mod(y + dy, m);
    }
    assert(w);
    assert(w <= m * n);
    assert(x == r);
    assert(y == c);
    l q = size - (size / w) * w;
    F(i, 0, q) {
      l x_ = mod(r + i * dx, n);
      l y_ = mod(c + i * dy, m);
      F(k, 0, h) tail[k] = mod(tail[k] * A + v[x_][y_], hh[k]);
    }
    F(i, 0, w) {
      vl a(h);
      vl f = full_hash;
      vl p(h); F(k, 0, h) p[k] = pows[k][w];
      l t = size / w;
      while (t) {
        if (t % 2) {
          F(k, 0, h) a[k] = mod(a[k] * p[k] + f[k], hh[k]);
        }
        F(k, 0, h) {
          f[k] = mod(f[k] * p[k] + f[k], hh[k]);
          p[k] = mod(p[k] * p[k], hh[k]);
        }
        t = t / 2;
      }
      F(k, 0, h) a[k] = mod(a[k] * pows[k][q] + tail[k], hh[k]);
      freq[make_tuple(a[0], a[1], a[2])]++;
      x = mod(r + i * dx, n);
      y = mod(c + i * dy, m);
      // LOG << a << " " << x << ' ' << y << ' ';
      // F(j, 0, size)
        // LOG << (char)(v[mod(r + (i + j) * dx, n)][mod(c + (i + j) * dy, m)] - 1 + 'a');
      // LOG << endl;
      l tx = mod(r + (i + q) * dx, n);
      l ty = mod(c + (i + q) * dy, m);
      F(k, 0, h) {
        full_hash[k] = mod(full_hash[k] - v[x][y] * pows[k][w - 1], hh[k]);
        full_hash[k] = mod(full_hash[k] * A + v[x][y], hh[k]);
        if (q) {
          tail[k] = mod(tail[k] - v[x][y] * pows[k][q - 1], hh[k]);
          tail[k] = mod(tail[k] * A + v[tx][ty], hh[k]);
        }
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m, k;
  cin >> n >> m >> k;
  vvl v(n, vl(m));
  F(i, 0, n) {
    string s;
    cin >> s;
    assert((l)s.size() == m);
    F(j, 0, m) {
      v[i][j] = s[j] - 'a' + 1;
      assert(v[i][j] < A);
    }
  }
  unordered_map<tuple<l,l,l>, l> freq;
  l h = 3;
  auto hh = get_hash_primes(h);
  vvl pows(h, vl(n * m + 1));
  F(i, 0, h) {
    pows[i][0] = 1;
    F(j, 1, n * m + 1) pows[i][j] = (pows[i][j - 1] * A) % hh[i];
  }
  F(dx, -1, 2) F(dy, -1, 2) {
    if (dx == 0 and dy == 0) continue;
    add(v, pows, hh, freq, dx, dy, k);
  }
  l a = 0, b = (n * m * 8); b *= b;
  for (auto kv : freq) {
    // LOG << kv.first << ' ' << kv.second << endl;
    a += (kv.second) * (kv.second);
  }
  l g = gcd(a, b);
  assert(g);
  cout << (a / g) << '/' << (b / g) << lf;
}
