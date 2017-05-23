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

const l MOD = e9 + 9;

struct BIT {
  vl tree;
  l max_p;
  BIT(size_t n) {
    max_p = n;
    tree.resize(n + 1);
  };
  // sum of [1, p], O(log(max))
  l get(l p) {
    l sum = 0;
    while (p) {
      sum += tree[p];
      sum %= MOD;
      p -= (p & -p);
    }
    return sum;
  }
  // O(log(max))
  void add(l p, l value) {
    while (p <= max_p) {
      tree[p] += value;
      tree[p] %= MOD;
      p += (p & -p);
    }
  }
  // find lowest index with given sum, -1 if not found O(log(max))
  l find(l sum) {
    l mask = max_p;
    while (true) {
      l lower = (mask & -mask);
      if (lower == mask) break;
      mask -= lower;
    }
    l p = 0;
    l top = -1;
    while (mask != 0) {
      l m = p + mask;
      if (m <= max_p) {
        if (sum == tree[m]) top = m;
        if (sum > tree[m]) {
          p = m;
          sum -= tree[m];
        }
      }
      mask >>= 1;
    }
    if (sum != 0) return top;
    return p;
  }
};


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n; cin >> n;
  map<l, l> idx;
  l sum = 0;
  idx[0] = 0;
  vl v(n);
  F(i, 0, n) {
    cin >> v[i];
    sum += v[i];
    idx[sum] = sum;
  }
  l t = 1;
  for (auto& kv : idx) kv.second = t++;
  BIT f(t);
  sum = 0;
  f.add(idx[0], 1);
  for (l i : v) {
    sum += i;
    t = f.get(idx[sum]) % MOD;
    f.add(idx[sum], t);
  }
  cout << t << endl;
}
