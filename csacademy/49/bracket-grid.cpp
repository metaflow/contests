#if defined(LOCAL)
#define PROBLEM_NAME "bracket-grid"
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
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

char inv(char& c) {
  char y = c;
  if (y == '(') c = ')'; else c = '(';
  return y;
}

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  vector<string> v(35 * 4, string(35 * 4 + 1, ')'));
  F(i, 0, v.size()) {
    if (i % 2 == 0) v[i].back() = '(';
  }
  F(i, 0, 33) {
    for (l j = i * 4; j < i * 4 + 5; j += 2) {
      for (l k = i * 4; k < i * 4 + 5; k += 2) {
        if (k == i * 4 + 2 and j == i * 4 + 2) continue;
        v[j][k] = '(';
      }
    }
    if (n % 2) {
      for (l k = i * 4; k < v[0].size(); k += 2) v[i * 4][k] = '(';
    }
    n /= 2;
  }
  cout << v.size() << ' ' << v[0].size() << lf;
  for (auto s : v) cout << s << lf;
}

l dfs(l r, l c, l open, vector<string>& s, l h, l w, vector<vvl>& dp) {
  if (r >= h or c >= w or open < 0 or open >= max(h, w)) return 0;
  auto& t = dp[r][c][open];
  if (t == -1) {
    if (s[r][c] == ')') open--; else open++;
    t = dfs(r + 1, c, open, s, h, w, dp) + dfs(r, c + 1, open, s, h, w, dp);
  }
  return t;
}

bool solution_checker(istream& input, istream& /* expected */,
                      istream& actual, ostream& out) {
  l n; input >> n;
  l h, w; actual >> h >> w;
  vector<string> s(h);
  F(i, 0, h) actual >> s[i];
  vector<vvl> dp(h, vvl(w, vl(max(h, w), -1)));
  if (s[h - 1][w - 1] != ')') {
    cout << "bad ending" << lf;
    return false;
  }
  dp[h - 1][w - 1][1] = 1;
  l e = dfs(0, 0, 0, s, h, w, dp);
  out << e << ' ' << n << lf;
  return e == n;
}

// return false to stop
bool generate_random(l tc, ostream& cout) {
  cout << tc << lf;
  return tc < 1000;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
