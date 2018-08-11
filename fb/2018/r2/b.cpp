#if defined(LOCAL)
#define PROBLEM_NAME "#PROBLEM_NAME"
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
#include <queue> // TODO: update template

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
// TODO: what with "readlink" on mac?
void solve(istream& in, ostream& out) {
  l tcc; in >> tcc;
  F(tc, 1, tcc + 1) {
    l n, m, a, b; in >> n >> m >> a >> b;
    vl parent(n, -1);
    vl children(n);
    vl buyers(n);
    vvl candies(n);
    F(i, 1, n) {
      l p; in >> p;
      parent[i] = p;
      children[p]++;
    }
    F(i, 0, m) {
      l x = (a * i + b) % n;
      buyers[x]++;
    }
    queue<l> q;
    l z = 0;
    F(i, 0, n) if (children[i] == 0) q.emplace(i);
    while (!q.empty()) {
      l u = q.front(); q.pop();
      candies[u].emplace_back(u);
      sort(all(candies[u]));
      F(i, 0, buyers[u]) {
        if (candies[u].empty()) break;
        z += candies[u].back();
        candies[u].pop_back();
      }
      l p = parent[u];
      if (p == -1) continue;
      children[p]--;
      if (children[p] == 0) q.emplace(p);
      copy(all(candies[u]), back_inserter(candies[p]));
    }
    out << "Case #" << tc << ": " << z << lf;
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
