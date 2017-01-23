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
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

// invariant: answer is within (a, b], f(a) = false, f(b) = true
l binary_search_lower(l a, l b, function<bool(l)> f) {
  while (b - a > 1) {
    l m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

l size(l w, l h) {
  if (w >= h) return max(l(0), h * (h + 1) / 2);
  return max(l(0), (h - w) * w + w * (w + 1) / 2);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m, k;
  while (cin >> n >> m >> k) {
    m -= n;
    l md = binary_search_lower(-1, m, [&](l d) {
      l h = m - d;
      l s = h + size(k - 1, h - 1) + size(n - k, h - 1);
      return s <= m;
    });
    m -= md;
    cout << m + 1 << endl;
  }
}
