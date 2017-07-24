#if defined(LOCAL)
#define PROBLEM_NAME "recurrentontree"
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

const l MOD = e9 + 7;

// 0 1
// 2 3

vl multiply(vl m1, vl m2) {
  vl r(4);
  r[0] = (m1[0] * m2[0] + m1[1] * m2[2]) % MOD;
  r[1] = (m1[0] * m2[1] + m1[1] * m2[3]) % MOD;
  r[2] = (m1[2] * m2[0] + m1[3] * m2[2]) % MOD;
  r[3] = (m1[2] * m2[1] + m1[3] * m2[3]) % MOD;
  return r;
}

vl add(vl m1, vl m2) {
  vl r(4);
  F(i, 0, 4) r[i] = (m1[i] + m2[i]) % MOD;
  return r;
}

vl __fibonacci_m_pow(vl &a, l n) {
  if (n <= 1) return a;
  vl m1, m2;
  if (n % 2 == 0) {
    m1 = m2 = __fibonacci_m_pow(a, n / 2);
  } else {
    m1 = a;
    m2 = __fibonacci_m_pow(a, n - 1);
  }
  return multiply(m1, m2);
}

// n >= 1, {1, 1, 2, 3, 5, ...}
vl fibonacci(l n) {
  vl a(4);
  if (n == 0) {
    a[0] = 1; a[1] = 0; a[2] = 0; a[3] = 1;
    return a;
  }
  a[0] = 1; a[1] = 1; a[2] = 1; a[3] = 0;
  return __fibonacci_m_pow(a, n);
}

struct Graph {
  vvl adj;
  vvl up;
  vl depth;
  vvl values, paths;
  vl fib;

  Graph(l n) {
    adj.resize(n);
    fib.resize(n);
    depth.resize(n);
    values.resize(n, vl(4));
    paths.resize(n, vl(4));
    l k = 0;
    while ((1 << k) <= n) k++;
    up.resize(k, vl(n, -1));
  }

  void build_up(l a) {
    F(i, 1, up.size()) {
      l t = up[i - 1][up[i - 1][a]];
      if (t == -1) break;
      up[i][a] = t;
    }
  }

  l walk(l a, l d) {
    l k = 0;
    while (d > 0) {
      if (d % 2) a = up[k][a];
      d /= 2;
      k++;
    }
    return a;
  }

  l lca(l a, l b) {
    a = walk(a, depth[a] - depth[b]);
    b = walk(b, depth[b] - depth[a]);
    if (a == b) return a;
    B(i, 0, up.size()) {
      if (up[i][a] != up[i][b]) {
        a = up[i][a];
        b = up[i][b];
      }
    }
    return up[0][a];
  }

  void dfs(l root) {
    auto fc = (fibonacci(fib[root]));
    vl s(4);
    for (auto i : adj[root]) {
      if (i == up[0][root]) continue;
      up[0][i] = root;
      dfs(i);
      values[root] = add(values[root], multiply(s, paths[i]));
      s = add(s, paths[i]);
    }
    values[root] = add(values[root], s);  // ends here
    values[root] = add(values[root], values[root]);
    values[root] = add(fc, multiply(fc, values[root]));
    paths[root] = add(fc, multiply(fc, s));
  }
};

void solve(istream& cin, ostream& cout) {
  l N; cin >> N;
  Graph g(N);
  F(i, 0, N - 1) {
    l a, b; cin >> a >> b; a--; b--;
    g.adj[a].emplace_back(b);
    g.adj[b].emplace_back(a);
  }
  F(i, 0, N) cin >> g.fib[i];
  g.dfs(0);
  vl s(4);
  F(i, 0, N) s = add(s, (g.values[i]));
  cout << s[0] << lf;
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
