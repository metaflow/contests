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

// finds lowest x: f(x) = true, x within [a, b), b if f(b - 1) = false
l binary_search_lower(l a, l b, function<bool(l)> f) {
  l count = b - a;
  while (count > 0) {
    l step = count / 2;
    l m = a + step;
    if (f(m)) { // TODO
      count = step;
    } else {
      a = m + 1;
      count -= step + 1;
    }
  }
  return a;
}

// # <= max_cost
l count_cost(vvl& v, l p, l max_cost, l cost) {
  if (cost > max_cost) return 0;
  if (p == -1) return 1;
  if (cost == max_cost) return 1;
  l r = 0;
  for (const auto x : v[p]) {
    r += count_cost(v, p - 1, max_cost, cost + x);
  }
  return r;
}

l sum_negative_cost(vvl& v, l p, l max_cost, l cost) {
  if (cost >= max_cost) return 0;
  if (p == -1) return max_cost - cost;
  if (cost == max_cost) return 0;
  l r = 0;
  for (const auto x : v[p]) r += sum_negative_cost(v, p - 1, max_cost, cost + x);
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ifstream fin("roboherd.in"); cin.rdbuf(fin.rdbuf());
  ofstream fout("roboherd.out"); cout.rdbuf(fout.rdbuf());
  l n, k;
  cin >> n >> k;
  vvl v(n);
  l base_cost = 0;
  l hi = 0;
  F(i, 0, n) {
    l s; cin >> s;
    F(j, 0, s) {
      l x; cin >> x;
      v[i].emplace_back(x);
    }
    sort(all(v[i]));
    l t = v[i][0];
    base_cost += t;
    for (auto& a : v[i]) a -= t;
    hi += v[i].back();
  }
  sort(all(v), [](const vl& a, const vl& b) {
      F(i, 1, min(a.size(), b.size())) {
        if (a[i] - a[i - 1] != b[i] - b[i - 1])
          return a[i] - a[i - 1] > b[i] - b[i - 1];
      }
      return a.size() > b.size();
    });
  l cost = binary_search_lower(0, hi, [&](l x) {
      return count_cost(v, n - 1, x, 0) >= k;
    });
  l answer = base_cost * k + cost * k - sum_negative_cost(v, n - 1, cost, 0);
  cout << answer << lf;
}
