#if defined(LOCAL)
#define PROBLEM_NAME "b"
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

bool good(l x, l y, vvl& colors) {
  return (x > -1 and x < colors.size() and
          y > -1 and y < colors[0].size() and
          colors[x][y] == 0);
}

void solve(istream& cin, ostream& cout) {
  l rows, cols, n;
  cin >> rows >> cols >> n;
  vl v(n); F(i, 0, n) cin >> v[i];
  l x = 0, y = 0;
  vvl colors(rows, vl(cols));
  l k = 0;
  l dx[] = {0, 1, 0, -1};
  l dy[] = {1, 0, -1, 0};
  F(i, 0, rows * cols) {
    while (v[k] == 0) k++;
    colors[x][y] = k + 1;
    v[k]--;
    F(j, 0, 4) {
      if (good(x + dx[j], y + dy[j], colors)) {
        x = x + dx[j];
        y = y + dy[j];
        break;
      }
    }
  }
  F(i, 0, rows) {
    F(j, 0, cols) {
      if (j) cout << ' ';
      cout << colors[i][j];
    }
    cout << lf;
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
