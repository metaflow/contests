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

vl get_possible(l a, vvl& adj, vl& value) {
  set<l> used;
  l wild = 0;
  for (auto b : adj[a]) {
    if (value[b] == -1) {
      wild++;
    } else {
      used.emplace(value[b]);
    }
  }
  l i = 0;
  vl v;
  F(j, 0, wild + 1) {
    while (used.count(i)) i++;
    if (i > adj[a].size()) break;
    v.emplace_back(i);
    i++;
  }
  return v;
}

bool find_assignment(vvl& adj, vvl& back, vl outgoing, vl value, l check) {
  queue<l> q;
  l n = adj.size();
  // assign obvious ones
  F(i, 0, n) if (value[i] == -1 and outgoing[i] == 0) q.emplace(i);
  while (not q.empty()) {
    l a = q.front(); q.pop();
    auto p = get_possible(a, adj, value);
    L("possible", a, p);
    if (p.empty()) return false;
    assert(p.size() == 1);
    if (value[a] != -1 and value[a] != p[0]) return false;
    value[a] = p[0];
    for (auto b : back[a]) {
      outgoing[b]--;
      if (outgoing[b] == 0) q.emplace(b);
    }
  }
  F(i, 0, n) {
    if (value[i] != -1) continue;
    for (auto b : back[i]) outgoing[b]--;
    auto p = get_possible(i, adj, value);
    L("possible", p);
    for (auto j : p) {
      value[i] = j;
      if (find_assignment(adj, back, outgoing, value, i)) return true;
    }
    return false;
  }
  return true;
}

void solve(istream& cin, ostream& cout) {
  l n;
  while (cin >> n) {
    L("------------");
    vvl adj(n), back(n);
    vl outgoing(n);
    vl value(n, -1);
    F(i, 0, n) {
      l a; cin >> a; a--;
      adj[a].emplace_back(i);
      outgoing[a]++;
      back[i].emplace_back(a);
    }
    if (find_assignment(adj, back, outgoing, value, -1)) {
      cout << "POSSIBLE" << lf;
    } else {
      cout << "IMPOSSIBLE" << lf;
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
