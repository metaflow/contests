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

class SegmentedTree {
  l n;
  vl v, low, high, delta;

  void init(l i, l a, l b) {
    low[i] = a;
    high[i] = b;
    if (a == b) return;
    l m = a + (b - a) / 2;
    init(2 * i, a, m);
    init(2 * i + 1, m + 1, b);
  }

  void propagate(l p) {
    delta[2 * p] += delta[p];
    delta[2 * p + 1] += delta[p];
    delta[p] = 0;
  }

  l merge(l a, l b) {
    return min(a, b);
  }

  l get(l p, l a, l b) {
    if (b < low[p] or high[p] < a) return numeric_limits<l>::max();
    if (a <= low[p] and high[p] <= b) {
      return v[p] + delta[p];
    }
    propagate(p);
    auto r = merge(get(p * 2, a, b),
                   get(p * 2 + 1, a, b));
    update(p);
    return r;
  }

  void update(l p) {
    v[p] = merge(get(p * 2, low[p], high[p]),
                 get(p * 2 + 1, low[p], high[p]));
  }

  void add(l p, l a, l b, l value) {
    if (b < low[p] or high[p] < a) return;

    if (a <= low[p] and high[p] <= b) {
      delta[p] += value;
      return;
    }

    propagate(p);
    add(2 * p, a, b, value);
    add(2 * p + 1, a, b, value);
    update(p);
  }

public:
  SegmentedTree(l size) {
    n = 1;
    while (n < size) n = n << 1;
    n = n << 1;
    v.resize(n);
    low.resize(n);
    high.resize(n);
    delta.resize(n);
    init(1, 0, size - 1);
  }

  void add(l a, l b, l value) {
    add(1, a, b, value);
  }

  l get(l a, l b) {
    return get(1, a, b);
  }
};

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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  F(k, 1, 100) {
    F(tc, 0, 1000) {
      l n = random_in_range(1, k + 1);
      vl v(n);
      SegmentedTree t(n);
      l a = random_in_range(0, n);
      l b = random_in_range(a, n);
      l d = random_in_range(-10, 11);
      if (random_bool()) {
        F(i, a, b + 1) v[i] += d;
        t.add(a, b, d);
      } else {
        l x = v[a];
        F(i, a + 1, b + 1) x = min(x, v[i]);
        assert(x == t.get(a, b));
      }
    }
  }
  cout << "PASSED" << lf;
}
