#if defined(LOCAL)
#define PROBLEM_NAME "FILLMTR"
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
  l d;
};

struct Graph {
  l v_count, e_count;
  vector<vector<Edge>> adj;
  vector<Edge> edges;
  vl value;

  Graph(l n) {
    v_count = n;
    adj.resize(n);
    value.resize(v_count, -1);
    e_count = 0;
  }

  void add_undirected(l a, l b, l d) {
    Edge ab; ab.id = e_count; ab.from = a; ab.to = b; ab.d = d;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = e_count; ba.from = b; ba.to = a; ba.d = d;
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
  l tcc; cin >> tcc;
  while (tcc--) {
    l n, m; cin >> n >> m;
    Graph g(n);
    F(i, 0, m) {
      l a, b, d; cin >> a >> b >> d; a--; b--;
      g.add_undirected(a, b, d);
    }
    bool answer = true;
    vb visited(n);
    vl v(n);
    F(i, 0, n) {
      if (visited[i]) continue;
      queue<l> q;
      q.emplace(i);
      v[i] = 0;
      visited[i] = true;
      while (not q.empty() and answer) {
        l a = q.front(); q.pop();
        for (auto e : g.adj[a]) {
          l t = (v[a] + e.d) % 2;
          if (visited[e.to]) {
            answer = answer and (v[e.to] == t);
          } else {
            q.emplace(e.to);
            v[e.to] = t;
            visited[e.to] = true;
          }
        }
      }
    }
    cout << (answer ? "yes" : "no") << lf;
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
