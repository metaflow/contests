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
  l ay, dy, hy, am, dm, hm, ca, cd, ch;
  while (cin >> hy >> ay >> dy
         >> hm >> am >> dm
         >> ch >> ca >> cd) {
    l best = INF;
    for (l da = max(l(0), dm - ay + 1); da < 200; da++)
      for (l dd = 0; dd <= max(l(0), am - dy); dd++) {
        l a = da + ay, d = dd + dy;
        l t = hm / (a - dm);
        if (hm % (a - dm)) t++;
        l dh = max(l(0), t * (am - d) - hy + 1);
        best = min(best, ch * dh + ca * da + cd * dd);
      }
    cout << best << '\n';
  }

}
