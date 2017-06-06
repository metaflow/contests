#if defined(LOCAL)
#define PROBLEM_NAME "B"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

void solve(istream& cin, ostream& cout) {
  string s;
  char x, y;
  while (cin >> s >> x >> y) {
    l p = -1;
    string answer(s.size(), y);
    string small(s.size() - 1, y);
    F(i, 0, s.size()) {
      auto a = s[i];
      if (a > y) break;
      if (a == y) {
        p = i;
        continue;
      }
      if (a > x) {
        answer[i] = x;
        break;
      }
      if (a == x) {
        answer[i] = x;
        continue;
      }
      // a < x
      if (p == -1) {
        answer = small;
        break;
      } else {
        answer[p] = x;
        F(j, p + 1, answer.size()) answer[j] = y;
        break;
      }
    }
    l i = 0; while (i < answer.size() and answer[i] == '0') i++;
    answer = answer.substr(i);
    if (answer.empty()) answer = "-1";
    cout << answer << lf;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
