#if defined(LOCAL)
#define PROBLEM_NAME "d"
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

l calc(l a, vvl& adj, vl& value) {
  if (adj[a].size() == 0) return 0;
  if (adj[a].size() == 1) return 1 - value[adj[a][0]];
  if (adj[a].size() > 2) return -1;
  bool zero = false, one = false;
  F(i, 0, 2) {
    if (value[adj[a]] > 1) return -1;
    if (value[adj[a]]) { one = true; } else { zero = true; }
  }
  if (not zero) return -1;
  if (one) return 2;
  return 1;
}

void solve(istream& cin, ostream& cout) {
  l n;
  while (cin >> n) {
    vvl adj(n), back(n);
    vl outgoing(n);
    vl value(n, -1);
    F(i, 0 n) {
      l a; cin >> a; a--;
      adj[a].empace_back(i);
      back[i].empace_back(a);
      outgoing[a]++;
    }
    queue<l> q;
    F(i, 0, n) {if (outgoing[a] == 0) {q.emplace(a);}}
    bool ok = true;
    while (ok and not q.empty()) {
      l a = q.front(); q.pop();
      value[a] = calc(a, adj, value);
      ok = ok and value[a] != -1;
      for (auto b : back[a]) {
        outgoing[b]--;
        if (outgoing[b] == 0) q.emplace(b);
      }
    }
    F(i, 0, 2) {
      
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
