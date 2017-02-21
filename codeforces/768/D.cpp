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

double p(l x, vd& c, l k) {
  double r = 1;
  double g = k;
  for (l i = 1; i < k; i++) {
    r -= pow(((double)i)/g, x - i) * c[i];
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l k, q;
  while (cin >> k >> q) {
    vd c(k);
    for (l i = 1; i < k; i++) {
      c[k] = 1;
      for (l j = 1; j <= i; j++) c[k] *= i * ((double)(k - j + 1)) / ((double)k);
    }
    for (l i = 0; i < q; i++) {
      double a; cin >> a;
      a = a/2000;
      l b = k - 1;
      l s = 1;
      while (s) {
        if (p(b + s, c, k) > a - EPS) {
          s /= 2;
          if (s == 0) b++;
        } else {
          if (b + s + 1 < b) {
            s /= 2;
          } else {
            b += s + 1;
          }
          if ((s * 2 > s) and (b + s*2 > b)) s *= 2;
        }
      }
      cout << b << '\n';
    }
  }
}
