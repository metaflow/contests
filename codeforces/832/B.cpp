#if defined(LOCAL)
#define PROBLEM_NAME "B"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

#if defined(LOCAL)
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#endif

void solve(istream& cin, ostream& cout) {
  string good, s;
  while (cin >> good >> s) {
    vb g(260);
    for (auto c : good) g[c] = true;
    auto p = s.find('*');
    string start = s.substr(0, p);
    string end = "";
    if (p != string::npos) {
      end = s.substr(p + 1);
    }
    l n; cin >> n;
    F(k, 0, n) {
      string t; cin >> t;
      bool ok = true;
      if (p == string::npos) {
        ok = t.size() == s.size();
      } else {
        ok = t.size() >= (start.size() + end.size());
      }
      if (ok) {
        F(i, 0, start.size()) {
          ok = ok and ((t[i] == s[i]) or (s[i] == '?' and g[t[i]]));
        }
        l m = t.size() - end.size();
        F(i, start.size(), m) ok = ok and (not g[t[i]]);
        F(i, 0, end.size()) {
          ok = ok and ((t[i + m] == end[i]) or (end[i] == '?' and g[t[i + m]]));
        }
      }
      cout << (ok ? "YES" : "NO") << lf;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
#else
  solve(cin, cout);
#endif
}
