#if defined(LOCAL)
#define PROBLEM_NAME "c"
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
// TODO: update templace
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using lu = unsigned long long;
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
#define MAX(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__y:__x;})
#define MIN(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

void build_s(vvi& g, vvi& s, l n, l m) {
  F(i, 0, n) {
    if (g[i][0]) s[i][1] = 1;
    F(j, 1, m) {
      s[i][j + 1] = s[i][j];
      if (g[i][j] and not g[i][j - 1]) s[i][j + 1]++;
    }
  }
}

void build_e(vvi& g, vvi& e, l n, l m) {
  F(i, 0, n) {
    F(j, 1, m + 1) {
      e[i][j] = e[i][j - 1];
      if (not g[i][j] and g[i][j - 1]) e[i][j]++;
    }
  }
}

void solve(istream& cin, ostream& cout) {
  l n, m, q; cin >> n >> m >> q;
  vvi grid(n, vi(m));
  F(i, 0, n) {
    string s; cin >> s;
    F(j, 0, m) grid[i][j] = s[j] - '0';
  }
  vvi sc(n, vi(m + 1)), ec(n, vi(m + 1)); // TODO: multidimentional macro?
  {
    vvi connected(n, vi(m));
    F(i, 1, n) {
      F(j, 0, m) connected[i][j] = grid[i][j] & grid[i - 1][j];
    }
    build_s(connected, sc, n, m);
    build_e(connected, ec, n, m);
  }
  // l d = 0;
  // while ((1 << (d + 1)) <= n) d++;
  vector<tuple<l, l, l, l, l>> queries(q);
  F(i, 0, q) {
    cin >> get<0>(queries[i]) >> get<1>(queries[i])
        >> get<2>(queries[i]) >> get<3>(queries[i]);
    get<0>(queries[i])--; get<1>(queries[i])--;
    get<2>(queries[i]) -= get<0>(queries[i]);
  }
  vvi ss(n, vi(m + 1));
  vvi ee(n, vi(m + 1));
  build_s(grid, ss, n, m);
  build_e(grid, ee, n, m);
  bool ok = true;
  l t = 1;
  while (ok) {
    ok = false;
    F(i, 0, q) {
      auto& r = queries[i];
      if (get<2>(r) % 2) {
        get<4>(r) += ss[get<0>(r)][get<3>(r)];
        get<4>(r) -= ee[get<0>(r)][get<1>(r)];
        get<0>(r) += t;
        if (get<2>(r) > 1) {
          get<4>(r) -= sc[get<0>(r)][get<3>(r)];
          get<4>(r) += ec[get<0>(r)][get<1>(r)];
        }
      }
      get<2>(r) /= 2;
      ok = ok or get<2>(r);
    }
    F(i, 0, n - 2 * t + 1) {
      F(j, 0, m + 1) {
        ss[i][j] = ss[i][j] + ss[i + t][j] - sc[i + t][j];
        ee[i][j] = ee[i][j] + ee[i + t][j] - ec[i + t][j];
      }
    }
    t *= 2;
  }
  for (auto r : queries) cout << get<4>(r) << lf;
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
