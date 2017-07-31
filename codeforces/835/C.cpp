#if defined(LOCAL)
#define PROBLEM_NAME "C"
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

const l MAX = 100;

void solve(istream& cin, ostream& cout) {
  l N, Q, C;
  while (cin >> N >> Q >> C) {
    vector<vvl> v(C + 1, vvl(MAX + 2, vl(MAX + 2)));
    F(i, 0, N) {
      l x, y, a; cin >> x >> y >> a;
      v[a][x][y]++;
    }
    F(k, 0, C + 1) {
      F(x, 1, MAX + 2) F(y, 1, MAX + 2) {
        v[k][x][y] += v[k][x - 1][y] + v[k][x][y - 1] - v[k][x - 1][y - 1];
      }
    }
    while (Q--) {
      l t, x1, y1, x2, y2; cin >> t >> x1 >> y1 >> x2 >> y2;
      y1--; x1--;
      l answer = 0;
      F(k, 0, C + 1) {
        l r = v[k][x2][y2] - v[k][x2][y1] - v[k][x1][y2] + v[k][x1][y1];
        answer += r * ((k + t) % (C + 1));
      }
      cout << answer << lf;
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
