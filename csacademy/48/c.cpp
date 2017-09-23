#if defined(LOCAL)
#define PROBLEM_NAME "c"
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
#define max(a,b)({__typeof__(a)x=(a);__typeof__(b)y=(b);x>y?x:y;})
#define min(a,b)({__typeof__(a)x=(a);__typeof__(b)y=(b);x<y?x:y;})

void solve(istream& cin, ostream& cout) {
  string s;
  while (cin >> s) {
    vl frq(10);
    for (auto c : s) frq[c - '0']++;
    vector<string> answers;
    for (auto n = 0; n < 1000; n += 8) {
      string tail = to_string(n);
      while (tail.size() < min(3, s.size())) tail = '0' + tail;
      auto f = frq;
      for (auto c : tail) f[c - '0']--;
      bool ok = f[0] >= 0;
      l p = 0;
      F(j, 1, 10) {
        ok = ok and (f[j] >= 0);
        if (p == 0 and f[j]) p = j;
      }
      if (not ok or (f[0] > 0 and not p)) continue;
      string answer;
      if (p) {
        answer += char('0'+p);
        f[p]--;
        F(k, 0, 10) {
          F(j, 0, f[k]) answer += char('0'+k);
        }
        answer += tail;
        answers.emplace_back(answer);
      } else {
        F(j, 0, 10) ok = ok and f[j] == 0;
        if (ok and tail[0] != '0') answers.emplace_back(tail);
      }
    }
    if (answers.empty()) {
      cout << -1 << lf;
    } else {
      sort(all(answers));
      cout << answers[0] << lf;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
