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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // solution
  string s;
  while (cin >> s) {
    l q; cin >> q;
    F(i, 0, q) {
      l a, b; cin >> a >> b; a--;
      string p; cin >> p;
      bool ok = true;
      size_t j = 0;
      string start = "";
      while (j < p.size() and p[j] != '*') {
        start += p[j];
        j++;
      }
      if (start.size()) {
        ok = ok and s.substr(a, start.size()) == start;
      }
      if (j == p.size()) {
        ok = ok and (start.size() == (b - a));
        cout << (ok ? "Yes" : "No") << lf;
        continue;
      }
      a += start.size();
      ok = ok and (a <= b);
      if (!ok) { cout << "No" << lf; continue; }
      size_t k = p.size() - 1;
      while (p[k] != '*') k--;
      if (k + 1 < p.size()) {
        string tail = p.substr(k + 1);
        b -= tail.size();
        ok = (b >= 0) and (s.substr(b, tail.size()) == tail);
      }
      ok = ok and (a <= b);
      if (!ok) { cout << "No" << lf; continue; }
      string sub = "";
      while (j < p.size()) {
        if (p[j] == '*') {
          if (sub.size()) {
            auto f = s.find(sub, a);
            if (f == string::npos) {
              ok = false;
              break;
            }
            a = f + sub.size();
            if (a > b) {
              ok = false;
              break;
            }
            sub = "";
          }
        } else {
          sub += p[j];
        }
        j++;
      }
      ok = ok and (a <= b);
      cout << (ok ? "Yes" : "No") << lf;
    }
  }
}
