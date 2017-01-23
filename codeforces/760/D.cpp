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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vl ts;
    vl ps(n);
    l sum = 0;
    for (l i = 0; i < n; i++) {
      l t; cin >> t;
      // 1.
      l new_sum = sum + 20;
      // 2.
      auto it = lower_bound(ts.begin(), ts.end(), t - 90 + 1);
      if (it == ts.begin()) {
        new_sum = min(new_sum, l(50));
      } else {
        new_sum = min(new_sum, ps[distance(ts.begin(), it) - 1] + 50);
      }
      // 3.
      it = lower_bound(ts.begin(), ts.end(), t - 1440 + 1);
      if (it == ts.begin()) {
        new_sum = min(new_sum, l(120));
      } else {
        new_sum = min(new_sum, ps[distance(ts.begin(), it) - 1] + 120);
      }
      cout << (new_sum - sum) << endl;
      sum = new_sum;
      ts.emplace_back(t);
      ps[i] = new_sum;
    }
  }
}
