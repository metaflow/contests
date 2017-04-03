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
  string s;
  while (cin >> s) {
    l answer = 0;
    bool plus = true;
    l x = 0;
    for (char c : s) {
      switch (c) {
      case '+':
        if (not plus) x = -x;
        answer += x;
        x = 0;
        plus = true;
        break;
      case '-':
        if (not plus) x = -x;
        answer += x;
        x = 0;
        plus = false;
        break;
      default:
        l t = c - '0';
        x = x * 10 + t;
        break;
      }
    }
    if (not plus) x = -x;
    answer += x;
    vl v;
    while (answer) {
      v.emplace_back(answer % 10);
      answer /= 10;
    }
    if (v.empty()) v.emplace_back(0);
    reverse(ALL(v));
    for (l i : v) {
      cout << ">++++++++++++++++++++++++++++++++++++++++++++++++";
      F(j, 0, i) cout << '+';
      cout << '.';
    }
    cout << '\n';
  }
}
