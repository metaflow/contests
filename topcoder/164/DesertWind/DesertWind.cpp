#if defined(LOCAL)
#define PROBLEM_NAME "DesertWind"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x...) (x)
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
const l INF = numeric_limits<l>::max(), inf = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

class DesertWind {
public:
  int daysNeeded(vector<string> grid) {
    l rows = grid.size();
    l cols = grid[0].size();
    vvl w(rows, vl(cols, inf));
    F(i, 0, rows) F(j, 0, cols) {
      if (grid[i][j] == '*') w[i][j] = 0;
    }
    bool updated = true;
    while (updated) {
      updated = false;
      F(i, 0, rows) F(j, 0, cols) {
        if (grid[i][j] == 'X') continue;
        l l1 = INF, l2 = INF;
        F(di, -1, 2) F(dj, -1, 2) {
          l ni = i + di, nj = j + dj;
          if (ni < 0 or ni >= rows or nj < 0 or nj >= cols) continue;
          l t = w[ni][nj];
          if (t < l2) l2 = t;
          if (l2 < l1) swap(l1, l2);
        }
        l t = min(l1 + 3, l2 + 1);
        if (t < w[i][j]) {
          updated = true;
          w[i][j] = t;
        }
      }
    }
    // L(w);
    F(i, 0, rows) F(j, 0, cols) {
      if (grid[i][j] != '@') continue;
      if (w[i][j] == inf) return -1;
      return w[i][j];
    }
    assert(false);
    return 0;
  }
};

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  vector<string> grid(n);
  F(i, 0, n) cin >> grid[i];
  DesertWind d;
  cout << d.daysNeeded(grid) << lf;
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
