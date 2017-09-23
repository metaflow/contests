#if defined(LOCAL)
#define PROBLEM_NAME "WEASELTX"
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
#define max(a,b)({__typeof__(a)x=(a);__typeof__(b)y=(b);x>y?x:y;})
#define min(a,b)({__typeof__(a)x=(a);__typeof__(b)y=(b);x<y?x:y;})

struct Edge {
  l to, id, from;
};

struct Graph {
  l v_count, e_count;
  vector<vector<Edge>> adj;
  vector<Edge> edges;

  Graph(l n) {
    v_count = n;
    adj.resize(n);
    e_count = 0;
  }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = e_count; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = e_count; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    e_count++;
    edges.emplace_back(ab);
  }

  void add_directed(l a, l b) {
    Edge ab; ab.id = e_count; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    e_count++;
    edges.emplace_back(ab);
  }
};

void solve(istream& cin, ostream& cout) {
  l N, Q;
  cin >> N >> Q;
  Graph g(N);
  F(i, 0, N - 1) {
    l a, b; cin >> a >> b; g.add_undirected(a, b);
  }
  vl v(N); F(i, 0, N) cin >> v[i];
  vl depth(N);
  queue<l> q;
  q.emplace(0);
  vb visited(N);
  visited[0] = true;
  while (not q.empty()) {
    l a = q.front(); q.pop();
    for (auto e : g.adj[a]) {
      if (visited[e.to]) continue;
      visited[e.to] = true;
      depth[e.to] = depth[a] + 1;
      q.emplace(e.to);
    }
  }
  vl y(N);
  F(i, 0, N) y[depth[i]] ^= v[i];
  l m = 1;
  while ((1 << m) <= N) m++;
  l p = 1 << m;
  vvl dp(m + 1, vl(p));
  F(i, 0, N) dp[0][i] = y[i];
  F(i, 0, m) {
    F(j, 0, p) {
      l b = 1 << i;
      if (b & j) {
        dp[i + 1][j] = dp[i][j ^ b];
      } else {
        dp[i + 1][j] = dp[i][j] ^ dp[i][j ^ b];
      }
    }
  }
  F(i, 0, Q) {
    l d; cin >> d;
    if (d == 0) {
      cout << y[0] << lf;
    } else {
      d = (d - 1) % p;
      cout << dp[m][d] << lf;
    }
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
