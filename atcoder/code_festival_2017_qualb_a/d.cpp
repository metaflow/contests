#if defined(LOCAL)
#define PROBLEM_NAME "d"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define C(x, ...) ;
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
#define MAX(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__y:__x;})
#define MIN(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

l dd(l p, l d, vl& v, vvl& dp) {
  // d: 0 - original value, 1 - decreased by 1, 2 - 1
  if (p >= v.size()) return 0;
  l& z = dp[p][d];
  if (z == -1) {
    if (v.size() - p < 2) return z = 0;
    // skip it
    z = dd(p + 1, 0, v, dp);
    l t = v[p];
    if (d == 1) t--;
    if (d == 2) t = 1;
    if (t > 0) {
      // take it and decrease next by 1
      z = max(z, t + dd(p + 1, 1, v, dp));
      // take next
      z = max(z, v[p + 1] + dd(p + 2, 0, v, dp));
      // take next but 1
      if (v[p + 1] > 1) {
        z = max(z, v[p + 1] - 1 + dd(p + 1, 2, v, dp));
      }
    }
  }
  return z;
}

l f(vl& v) {
  if (v.empty()) return 0;
  vvl dp(v.size(), vl(3, -1));
  return dd(0, 0, v, dp);
}

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  string s; cin >> s;
  char prev = '0';
  l answer = 0;
  vl v;
  l run = 0;
  for (char c : s) {
    if (c == '1') {
      run++;
    } else {
      if (prev == '0') {
        answer += f(v);
        v.clear();
      } else {
        v.emplace_back(run);
      }
      run = 0;
    }
    prev = c;
  }
  if (run) v.emplace_back(run);
  answer += f(v);
  cout << answer << lf;
}

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}

// return false to stop
bool generate_random(l tc, ostream& cout) {
  l max_cases = 1000;
  if (tc % (max_cases / 100) == 0) cerr << (tc * 100 / max_cases) << "%\r";
  l n = tc / 10 + 1;
  string s(n, '0');
  F(i, 0, n) if (random_bool()) s[i] = '1';
  cout << n << lf << s << lf;
  return tc < max_cases;
}

l dfs(string s) {
  l z = 0;
  F(i, 1, s.size() - 1) {
    if (s[i - 1] == '1' and s[i] == '0' and s[i + 1] == '1') {
      auto a = s;
      a[i - 1] = a[i + 1] = '0';
      a[i] = '1';
      z = max(z, 1 + dfs(a));
    }
  }
  return z;
}

void solve_brute(istream& cin, ostream& cout) {
  l n; string s; cin >> n >> s;
  cout << dfs(s) << lf;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  _generate_random_test = generate_random;
  _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
