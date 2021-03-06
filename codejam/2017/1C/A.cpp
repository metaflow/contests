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

double area(double r1, double r2, double h) {
  LOG << r1 << ' ' << r2 << endl;
  return PI * (r2 * r2 - r1 * r1) + 2 * PI * r2 * h;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    cout << "Case #" << tc << ": ";
    l n, k; cin >> n >> k;
    vector<pair<double, double>> cake;
    double r = 0, h = 0;
    F(i, 0, n) {
      cin >> r >> h;
      cake.emplace_back(make_pair(r, h));
    }
    sort(all(cake));
    double answer = 0;
    vd hs;
    F(i, 0, n) {
      if (hs.size() == k - 1) {
        double v = 0;
        for (auto x : hs) v += x;
        v += area(0, cake[i].first, cake[i].second);
        answer = max(answer, v);
      }
      hs.emplace_back(2 * PI * cake[i].first * cake[i].second);
      sort(all(hs), greater<double>());
      while (hs.size() >= k) hs.pop_back();
    }
    cout << setprecision(9) << fixed << answer << lf;
  }
}
