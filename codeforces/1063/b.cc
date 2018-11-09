#if defined(LOCAL)
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
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <memory>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using ii = pair<int, int>;
using lu = unsigned long long;
using l = long long;
using vs = vector<string>;
using vii = vector<ii>;
using vl = vector<l>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using ll = pair<l, l>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using mll = unordered_map<l, l>;
using sl = unordered_set<l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const double PI = 3.14159265358979323846;
const l e0 = 1, e3 = 1000, e5 = 100000, e6 = 10 * e5, e7 = 10 * e6,
        e8 = 10 * e7, e9 = 10 * e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a, b, c) for (l a = l(b); a < l(c); a++)
#define B(a, b, c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

void solve(istream &in, ostream &out);
int main(int argc, char **argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  tst::test_init(argc, argv);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  tst::maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
const l MOD = e9 + 7; // end of template
// adj[u][?] = (v, x) - edge from u to v of weight x
vl shortest_paths(int from, vector<vector<ii>>& adj) {
  size_t n = adj.size();
  vl distance(n, INF);
  queue<size_t> q;
  vb in_queue(n, false);
  distance[from] = 0;
  q.emplace(from);
  while (!q.empty()) {
    size_t u = q.front(); q.pop(); in_queue[u] = false;
    for (auto e : adj[u]) {
      int v = e.first;
      int d = e.second;
      l t = distance[u] + d;
      if (t < distance[v]) {
        distance[v] = t;
        if (!in_queue[v]) {
          q.emplace(v);
          in_queue[v] = true;
        }
      }
    }
  }
  return distance;
}

void solve(istream &in, ostream &out) {
  l n, m, r0, c0, tl, tr; in >> n >> m >> r0 >> c0 >> tl >> tr;
  vs grid(n);
  F(i, 0, n) in >> grid[i];
  vvll b(n, vll(m, ll(-1, -1)));
  vvb in_queue(n, vb(m));
  queue<ll> q;
  r0--; c0--;
  q.emplace(r0, c0);
  b[r0][c0] = ll(tl, tr);
  in_queue[r0][c0] = true;
  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, 1, -1};
  while (!q.empty()) {
    l r, c;
    tie(r, c) = q.front(); q.pop();
    in_queue[r][c] = false;
    F(d, 0, 4) {
      l x = r + dr[d], y = c + dc[d];
      if (x < 0 or x >= n or y < 0 or y >= m) continue;
      if (grid[x][y] == '*') continue;
      auto t = b[r][c];
      if (dc[d] == 1) {
        t.second--;
        if (t.second < 0) continue;
      }
      if (dc[d] == -1) {
        t.first--;
        if (t.first < 0) continue;
      }
      if (b[x][y] < t) {
        b[x][y] = t;
        if (!in_queue[x][y]) {
          in_queue[x][y] = true;
          q.emplace(x, y);
        }
      }
    }
  }
  l z = 0;
  F(r, 0, n) F(c, 0, m) if (b[r][c].first >= 0) z++;
  out << z << lf;
}
