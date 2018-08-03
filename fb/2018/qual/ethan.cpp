#if defined(LOCAL)
#define PROBLEM_NAME "ethan"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#endif
#include <vector>
#include <string>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <math.h>

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = M_PI;
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

const l MOD = e9 + 7;

vl kmp_build_back(const string& p) {
  vl b(p.size());
  l j = -1;
  for (size_t i = 0; i < p.size(); i++) {
    b[i] = j;
    while ((j > -1) and (p[j] != p[i])) j = b[j];
    j++;
  }
  return b;
}

vl kmp_search(const string& s, const string& p, const vl& b) {
  vl matches;
  l j = 0;
  for (size_t i = 0; i < s.size(); i++) {
    while (j > -1 && p[j] != s[i]) j = b[j];
    j++;
    if (j == l(p.size())) {
      matches.emplace_back(i - j + 1);
      j = b[j];
    }
  }
  return matches;
}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
void solve(istream& cin, ostream& cout) {
#pragma clang diagnostic pop
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    cout << "Case #" << tc << ": ";
    string s; cin >> s;
    l non_perfect = 0;
    /*
    auto b = kmp_build_back(s);
    L(b);
    F(i, 1, b.size()) {
      if (b[i] == 1 &&
          ((b.back() != l(b.size()) - i) || s.back() != s[b.back()])) {
        non_perfect = i;
      }
    }
    */
    F(i, 1, s.size()) {
      if (s[i] != s[0]) continue;
      if (s.compare(i, s.size() - i, s, 0, s.size() - i)) {
        non_perfect = i;
      }
    }
    if (non_perfect) {
      cout << s.substr(0, non_perfect) << s << lf;
    } else {
      cout << "Impossible" << lf;
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
