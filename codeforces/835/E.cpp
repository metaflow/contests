#if defined(LOCAL)
#define PROBLEM_NAME "E"
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

void player_b(istream& hidden_state, ostream& log,
              istream& cin, ostream& cout) {
  l n, x, y; hidden_state >> n >> x >> y;
  vl v(n);
  F(i, 0, n) hidden_state >> v[i];
  cout << n << ' ' << x << ' ' << y << endl;
  char op;
  while (cin >> op) {
    if (op == '!') {
      l a, b; cin >> a >> b; a--; b--;
      if (v[a] != y or v[b] != y) {
        log << a + 1 << " -> " << v[a] << ", " << b + 1 << " -> " << v[b] << endl;
      }
      break;
    }
    l k; cin >> k;
    l t = 0;
    F(i, 0, k) {
      l a; cin >> a; a--;
      t = t ^ v[a];
    }
    cout << t << endl;
  }
}

l ask(set<l>& s, istream& cin, ostream& cout) {
  cout << "? " << s.size();
  for (auto a : s) cout << ' ' << a + 1;
  cout << endl;
  l r; cin >> r;
  return r;
}

void solve(istream& cin, ostream& cout) {
  l n, x, y; cin >> n >> x >> y;
  l t = 1;
  l m = 0;
  set<l> s;
  while (t < n) {
    set<l> part;
    F(i, 0, n) {
      if (i & t) part.emplace(i);
    }
    l r = ask(part, cin, cout);
    if (r == y or r == (x ^ y)) {
      s = part;
      m += t;
    }
    t = t * 2;
  }
  while (s.size() > 1) {
    set<l> a, b;
    l i = 0;
    for (auto j : s) if (i++ % 2) a.emplace(j); else b.emplace(j);
    l r = ask(a, cin, cout);
    if (r == y or r == (x ^ y)) s = a; else s = b;
  }
  l answer1 = *s.begin();
  l answer2 = answer1 ^ m;
  if (answer1 > answer2) swap(answer1, answer2);
  cout << "! " << answer1 + 1 << ' ' << answer2 + 1 << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
