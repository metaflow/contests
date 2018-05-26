#if defined(LOCAL)
#define PROBLEM_NAME "e"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#include <bits/stdc++.h>
#endif

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
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

void solve(istream& cin, ostream& cout) {
  l n, k, q; cin >> n >> k >> q;
  vl v(n); F(i, 0, n) cin >> v[i];
  auto start = v;
  sort(all(start));
  I(start);
  l z = INF;
  F(i, 0, n - q - k + 2) {
    if (i and start[i] == start[i - 1]) continue;
    l x = start[i];
    I(x);
    auto w = v;
    vl pick;
    l a = 0;
    while (a < n) {
      while (a < n and w[a] < x) a++;
      l b = a + 1;
      while (b < n and w[b] >= x) b++;
      I(a, b);
      if (I(b - a - k + 1) > 0) {
        sort(w.begin() + a, w.begin() + b);
        F(j, 0, b - a - k + 1) pick.emplace_back(w[a + j]);
      }
      a = b;
    }
    if (pick.size() < q) continue;
    sort(all(pick));
    z = min(z, pick[q - 1] - pick[0]);
  }
  cout << z << endl;
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
