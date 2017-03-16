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
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
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
  l a;
  while (cin >> a) {
    string s; cin >> s;
    vl v(s.size());
    F(i, 0, s.size()) v[i] = s[i] - '0';
    unordered_map<l, l> cs;
    F(i, 0, s.size()) {
      l sum = 0;
      F(j, i, s.size()) {
        sum += v[j];
        if (sum > a) break;
        if (sum == 0) {
          if (a == 0) cs[0]++;
          continue;
        }
        if (a % sum == 0) cs[sum]++;
      }
    }
    l answer = 0;
    if (a == 0) {
      answer = 2 * cs[0] * (s.size() * (s.size() + 1) / 2) - cs[0] * cs[0];
    } else {
      for (const auto& kv : cs) {
        l x = a / kv.first;
        if (cs.count(x) == 0) continue;
        l t = kv.second * cs[x];
        answer += t;
      }
    }
    cout << answer << '\n';
  }
}
