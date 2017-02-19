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
  l ts, tf, n, d;
  while (cin >> ts >> tf >> d >> n) {
    l best = numeric_limits<l>::max();
    l answer = 0;
    l t = ts; // time last served, exclusive
    vl v(n);
    for (l i = 0; i < n; i++) cin >> v[i];
    for (l i = 0; i < n; i++) {
      l x = v[i];
      // there is a gap
      if (x > t) {
        answer = t;
        break;
      }
      // try to go before
      if (x - 1 >= 0) {
        l k = t - x + 1;
        if (best > k) {
          best = k;
          answer = x - 1;
        }
      }
      // move time of last served
      t = max(x, t) + d;
      if (t + d > tf) break; // end
      // try to go with
      if ((i == n - 1) or (v[i] != v[i+1])) {
        l k = t - x;
        if (best > k) {
          best = k;
          answer = x;
        }
      }
    }
    // empty line at the end
    if (t + d <= tf) {
      answer = t;
    }
    cout << answer << '\n';
  }
}
