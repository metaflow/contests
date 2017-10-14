#if defined(LOCAL)
#define PROBLEM_NAME "skipping-subpath-sum"
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
#define MAX(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__y:__x;})
#define MIN(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

struct Edge {
  l to;
  l id, from;
  // l opposite; // for flow, index in 'to'
  // l capacity; // for flow
  // l cost;
};

struct Graph {
  l v, e; // number of vertices and edges
  vector<vector<Edge>> adj;

  Graph(l n): v(n), e(0) {
    adj.resize(v);
  }

  l add_node() { adj.resize(++v); return v - 1; }

  void add_simple(l a, l b) { // for tree-like
    Edge ab; ab.to = b;
    adj[a].emplace_back(ab);
    e++;
  }

  void add_undirected(l a, l b) {
    Edge ab; ab.id = e; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    Edge ba; ba.id = e; ba.from = b; ba.to = a;
    adj[b].emplace_back(ba);
    e++;
  }

  void add_directed(l a, l b) {
    Edge ab; ab.id = e; ab.from = a; ab.to = b;
    adj[a].emplace_back(ab);
    e++;
  }

  //  void add_flow(l a, l b, l w, l cost) {
  // Edge ab; ab.id = e; ab.from = a; ab.to = b; ab.capacity = w; ab.cost = cost;
  // ab.opposite = adj[b].size();
  // Edge ba; ba.id = e; ba.from = b; ba.to = a; ba.capacity = 0; ba.cost = 0;
  // e++;
  // ba.opposite = adj[a].size();
  // adj[a].emplace_back(ab);
  // adj[b].emplace_back(ba);
  // }
};

struct seg {
  l start, mid, end, total;
  seg(l x) {
    start = mid = end = MAX(0, x);
    total = x;
  }
  seg() : seg(0) {}
};
#if defined(LOCAL)
ostream& operator << (ostream& s, const seg& p) {
  s << make_tuple(p.start, p.mid, p.total, p.end);
  return s;
}
#endif

// a <- b <- .. <- root
seg merge(seg a, seg b) {
  seg z;
  z.start = max(a.start, a.total + b.start);
  z.mid = max(a.mid, max(b.mid, a.end + b.start));
  z.end = max(b.end, a.end + b.total);
  z.total = a.total + b.total;
  return z;
}

struct LCA {  // require 'graph'
  vvl up; // binary lift [i][j] jump of 2^i from j
  vector<vector<seg>> ss;
  vl depth; // depth[root] = 0
  vl value;

  LCA(Graph& g, l root, vl& color, l c, vi& v) {
    depth.resize(g.v);
    l k = 0;
    while ((1 << k) <= g.v) k++;
    up.resize(k, vl(g.v, -1));
    ss.resize(k, vector<seg>(g.v));
    value.resize(g.v);
    F(i, 0, g.v) {
      if (color[i] == c) value[i] = v[i];
    }

    queue<l> q;
    q.emplace(root);
    depth[root] = 0;
    while (not q.empty()) {
      l a = q.front(); q.pop();
      seg sa;
      for (auto e : g.adj[a]) {
        if (e.to == up[0][a]) continue;
        up[0][e.to] = a;
        ss[0][e.to] = seg(value[e.to]);
        depth[e.to] = depth[a] + 1;
        build_up(e.to);
        q.emplace(e.to);
      }
    }
  }

  void build_up(l a) {
    F(i, 1, up.size()) {
      l t = up[i - 1][up[i - 1][a]];
      if (t == -1) break;
      up[i][a] = t;
      ss[i][a] = merge(ss[i - 1][a], ss[i - 1][up[i - 1][a]]);
    }
  }

  pair<l, seg> walk(l a, l d) {  // walks up d levels
    l k = 0;
    seg s;
    while (d > 0) {
      if (d % 2) {
        s = merge(s, ss[k][a]);
        a = up[k][a];
      }
      d /= 2;
      k++;
    }
    return make_pair(a, s);
  }

  l lca(l a, l b) {
    seg sa, sb;
    if (depth[a] < depth[b]) swap(a, b);
    tie(a, sa) = walk(a, depth[a] - depth[b]);
    if (a == b) {
      // L(sa, value[b], "subtree");
      return max({(l)0, sa.mid, sa.end + value[a]});
    }
    B(i, 0, up.size()) {
      if (up[i][a] != up[i][b]) {
        sa = merge(sa, ss[i][a]);
        sb = merge(sb, ss[i][b]);
        a = up[i][a];
        b = up[i][b];
      }
    }
    sa = merge(sa, ss[0][a]);
    sb = merge(sb, ss[0][b]);
    a = up[0][a];
    // L(sa, sb, value[a], "merge");
    return max({(l)0, sa.mid, sb.mid, sa.end + value[a] + sb.end});
  }
};

vector <int> skippingSubpathSum(int n, vector<int>& v, vector<vector<int>>& graph, vector<pair<int, int>>& queries) {
  Graph g(n);
  F(i, 0, n) {
    for (auto j : graph[i]) {
      if (j < i) continue;
      g.add_undirected(i, j);
    }
  }
  vl color(n, -1);
  queue<l> q;
  q.emplace(0);
  color[0] = 0;
  while (not q.empty()) {
    l a = q.front(); q.pop();
    for (auto e : g.adj[a]) {
      if (color[e.to] != -1) continue;
      color[e.to] = 1 - color[a];
      q.emplace(e.to);
    }
  }
  LCA lca0(g, 0, color, 0, v), lca1(g, 0, color, 1, v);
  // L(lca0.value, lca1.value);
  l m = queries.size();
  vi z(m);
  F(i, 0, m) {
    l a, b; tie(a, b) = queries[i];
    z[i] = max(lca0.lca(a, b), lca1.lca(a, b));
  }
  return z;
}

void solve(istream& cin, ostream& cout) {
  int n;
  cin >> n;
  vector<int> c(n);
  for(int c_i = 0; c_i < n; c_i++){
    cin >> c[c_i];
  }
  vector<vector<int>> graph(n);
  for (int i = 0; i < n-1; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  int q;
  cin >> q;
  vector<pair<int, int>> queries;
  for (int i = 0; i < q; ++i) {
    int u, v;
    cin >> u >> v;
    queries.push_back(make_pair(u,v));
  }
  vector <int> answers = skippingSubpathSum(n, c, graph, queries);
  for (ssize_t i = 0; i < answers.size(); i++) {
    cout << answers[i] << (i != answers.size() - 1 ? "\n" : "");
  }
  cout << endl;
}

bool dfs(vector<vector<int>>&g, int v, int p, int target, vector<int>& path) {
    path.push_back(v);
    if (v == target) {
        return true;
    }
    for (auto u : g[v]) {
        if (u == p) continue;
        bool found = dfs(g, u, v, target, path);
        if (found) return true;
    }
    path.pop_back();
    return false;
}

/* 
 * Kadane's algorith: https://en.wikipedia.org/wiki/Maximum_subarray_problem
 */
int kadane(const vector<int>& a) {
    if (a.empty()) return 0;
    int max_ending_here = max(a[0], 0);
    int max_so_far = max_ending_here;
    for (int i = 1; i < a.size(); ++i) {
        max_ending_here = max(max(0, a[i]), max_ending_here+a[i]);
        max_so_far = max(max_so_far, max_ending_here);
    } 
    return max_so_far;
}

vector <int> skippingSubpathSumBrute(int /* n */, vector <int> c, vector < vector<int> > graph, vector <pair<int, int>> queries) {
    vector<int> answers(queries.size());
    for (int qid = 0; qid < queries.size(); ++qid) {
        int u = queries[qid].first;
        int v = queries[qid].second;
        vector<int> path;
        dfs(graph, u, -1, v, path);
        vector<int> oddPath;
        vector<int> evenPath;
        for (int i = 0; i < path.size(); ++i) {
            if ((i+1) % 2 == 0) {
                evenPath.push_back(c[path[i]]);
            } else {
                oddPath.push_back(c[path[i]]);
            }
        }
        int s1 = kadane(evenPath);
        int s2 = kadane(oddPath);
        answers[qid] = max(s1, s2);
    }
    return answers;
}

void solve_brute(istream& cin, ostream& cout) {
  int n;
  cin >> n;
  vector<int> c(n);
  for(int c_i = 0; c_i < n; c_i++){
    cin >> c[c_i];
  }
  vector<vector<int>> graph(n);
  for (int i = 0; i < n-1; ++i) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  int q;
  cin >> q;
  vector<pair<int, int>> queries;
  for (int i = 0; i < q; ++i) {
    int u, v;
    cin >> u >> v;
    queries.push_back(make_pair(u,v));
  }
  vector <int> answers = skippingSubpathSumBrute(n, c, graph, queries);
  for (ssize_t i = 0; i < answers.size(); i++) {
    cout << answers[i] << (i != answers.size() - 1 ? "\n" : "");
  }
  cout << endl;
}

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}


// return false to stop
bool generate_random(l tc, ostream& cout) {
  l max_cases = 100;
  if (tc % (max_cases / 100) == 0) cerr << (tc * 100 / max_cases) << "%\r";
  l n = tc / 10 + 1;
  cout << n << lf;
  F(i, 0, n) cout << random_in_range(-10, 10) << ' ';
  cout << lf;
  F(i, 1, n) cout << random_in_range(0, i) << ' ' << i << lf;
  l q = 10;
  cout << q << lf;
  F(i, 0, q) {
    cout << random_in_range(0, n) << ' ' << random_in_range(0, n) << lf;
  }
  return tc < max_cases;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  _generate_random_test = generate_random;
  _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
