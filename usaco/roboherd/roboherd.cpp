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
    if (f(m)) {
      count = step;
    } else {
      a = m + 1;
      count -= step + 1;
    }
  }
  return a;
}

l c;
l target_count;
l max_cost;
vvl v;
// # <= max_cost
bool count_cost(l p, l cost) {
  // if (cost > max_cost) return false;
  if (p == -1 or (v[p].size() > 0 and cost + v[p][1] > max_cost)) {
    c++;
    return (c >= target_count);
  }
  for (const auto x : v[p]) {
    if (cost + x > max_cost) break;
    if (count_cost(p - 1, cost + x))
      return true;
  }
  return false;
}

l sum_negative_cost(l p, l cost) {
  // if (cost >= max_cost) return 0;
  if (p == -1 or (v[p].size() > 0 and cost + v[p][1] >= max_cost))
    return max_cost - cost;
  l r = 0;
  for (const auto x : v[p]) {
    if (x + cost >= max_cost) break;
    r += sum_negative_cost(p - 1, cost + x);
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ifstream fin("roboherd.in"); cin.rdbuf(fin.rdbuf());
  ofstream fout("roboherd.out"); cout.rdbuf(fout.rdbuf());
  l n;
  cin >> n >> target_count;
  v.resize(n);
  l base_cost = 0;
  l hi = 0;
  F(i, 0, n) {
    l s; cin >> s;
    v[i].resize(s);
    F(j, 0, s) cin >> v[i][j];
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
  max_cost = binary_search_lower(0, hi, [&](l x) {
      c = 0;
      max_cost = x;
      return count_cost(n - 1, 0);
    });
  l answer = base_cost * target_count
    + max_cost * target_count
    - sum_negative_cost(n - 1, 0);
  cout << answer << lf;
}
