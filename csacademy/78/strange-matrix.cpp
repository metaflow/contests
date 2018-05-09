#if defined(LOCAL)
#define PROBLEM_NAME "strange-matrix"
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
using l = long long; using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
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

// [0, size), get / add intervals are inclusive
class SegmentTree {
  l n, m;
  // inclusive range [low[i], high[i]]
  vl low, high; // TODO: update snippet
  vvvl v;

  void init(l i, l a, l b) {
    low[i] = a;
    high[i] = b;
    if (a == b) return;
    l k = a + (b - a) / 2;
    init(2 * i, a, k);
    init(2 * i + 1, k + 1, b);
    update(i);
  }

  void update(l p) {
    l i = p * 2, j = p * 2 + 1;
    F(a, 0, m) F(b, 0, m) v[p][a][b] = -1;
    F(a, 0, m) {
      F(b, 0, m) {
        if (abs(a - b) > (high[i] - low[i])) continue;
        F(c, 0, m) {
          if (abs(b - c) > 1) continue;
          F(d, 0, m) {
            if (abs(c - d) > (high[j] - low[j])) continue;
            v[p][a][d] = max(v[p][a][d], v[i][a][b] + v[j][c][d]);
          }
        }
      }
    }
  }

  void set(l p, l x, l y, l value) {
    if (y < low[p] or high[p] < y) return;
    if (low[p] == high[p]) {
      v[p][x][x] = value;
      return;
    }
    set(2 * p, x, y, value);
    set(2 * p + 1, x, y, value);
    update(p);
  }

  void set_raw(l p, l x, l y, l value) {
    if (y < low[p] or high[p] < y) return;
    if (low[p] == high[p]) {
      v[p][x][x] = value;
      return;
    }
    set_raw(2 * p, x, y, value);
    set_raw(2 * p + 1, x, y, value);
  }

  void update_all(l p) {
    if (low[p] == high[p]) return;
    update_all(p * 2);
    update_all(p * 2 + 1);
    update(p);
  }

public:
  l size;
  SegmentTree(l rows, l cols) {
    size = cols;
    n = 1;
    while (n < size) n = n << 1;
    m = rows;
    n = n << 1;
    v.resize(n, vvl(m, vl(m)));
    low.resize(n);
    high.resize(n);
    init(1, 0, size - 1);
  }

  void set(l x, l y, l value) {
    set(1, x, y, value);
  }

  void set_raw(l x, l y, l value) {
    set_raw(1, x, y, value);
  }

  l get() {
    l z = -1;
    F(a, 0, m) F(b, 0, m) {
      if (abs(b - a) >= size) continue;
      z = max(z, v[1][a][b]);
    }
    return z;
  }

  void update_all() {
    update_all(1);
  }
};


void solve(istream& cin, ostream& cout) {
  l n, m, q; cin >> n >> m >> q;
  SegmentTree s(n, m);
  F(i, 0, n) F(j, 0, m) {
    l x;
    cin >> x;
    s.set_raw(i, j, x);
  }
  s.update_all();
  F(i, 0, q) {
    l x, y, k; cin >> x >> y >> k; x--; y--;
    s.set(x, y, k);
    cout << s.get() << lf;
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
