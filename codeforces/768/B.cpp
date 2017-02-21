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

vl dp;

l get_length(l n, l p) {
  if (n < 2) return 1;
  l& r = dp[p];
  if (r == 0) {
    r = 1 + 2 * get_length(n / 2, p + 1);
  }
  return r;
}

vl fulls;

l count_ones(l from, l to, l n, l p) {
  if (n < 2) return n % 2;
  l h = get_length(n / 2, p + 1);
  if ((from == 0) and (to == get_length(n, p))) {
    l &r = fulls[p];
    if (r == -1) {
      r = n % 2 + 2 * count_ones(0, h, n / 2, p + 1);
    }
    return r;
  }
  l r = 0;
  if (from <= h && to > h) r+= n % 2;
  if (from < h) r += count_ones(from, min(h, to), n / 2, p + 1);
  if (to > h + 1) r += count_ones(max(l(0), from - h - 1), to - h - 1, n / 2, p + 1);
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, from, to;
  while (cin >> n >> from >> to) {
    dp.clear();
    dp.resize(1000, 0);
    fulls.clear();
    fulls.resize(1000, - 1);
    // l total = get_length(n, 0);
    cout << count_ones(from - 1, to, n, 0) << '\n';
  }
}
