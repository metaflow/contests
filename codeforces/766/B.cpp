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
    vl v(n);
    for (l i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    bool ok = false;
    for (l i = 0; (i < n - 1) and not ok; i++) {
      l a = v[i + 1] - v[i] + 1;
      l b = v[i + 1] + v[i] - 1;
      l x = lower_bound(v.begin(), v.end(), a) - v.begin();
      if (x >= n) continue;
      l y = lower_bound(v.begin(), v.end(), b + 1) - v.begin();
      for (l j = x; j < y; j++) {
        if (j == i or j == i + 1) continue;
        ok = true;
        break;
      }
    }
    cout << (ok ? "YES" : "NO") << '\n';
  }
}
