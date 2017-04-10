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
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
#define ALL(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

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
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    string s; l k; cin >> s >> k;
    l answer = 0;
    vb f; for (auto c : s) f.emplace_back(c == '+');
    F(i, 0, s.size() - k + 1) {
      if (not f[i]) {
        answer++;
        F(j, i, i + k) f[j] = not f[j];
      }
    }
    bool ok = true;
    for (auto b : f) ok = ok and b;
    cout << "Case #" << tc << ": ";
    if (ok) {
      cout << answer << '\n';
    } else {
      cout << "IMPOSSIBLE\n";
    }
  }
}
