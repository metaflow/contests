#if defined(LOCAL)
#define PROBLEM_NAME "AngelDemonGame"
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

struct Edge {
  l to;
  l id, from;
  l opposite; // index in 'to'
  l capacity; // for flow
  l cost;
};

struct Graph {
  l v, e; // number of vertices and edges
  vector<vector<Edge>> adj;

  Graph(l n): v(n), e(0) {
    adj.resize(v);
  }

  l add_node() {
    v++;
    adj.resize(v);
    return v - 1;
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

  void add_flow(l a, l b, l w, l cost) {
    Edge ab; ab.id = e; ab.from = a; ab.to = b; ab.capacity = w; ab.cost = cost;
    ab.opposite = adj[b].size();
    Edge ba; ba.id = e; ba.from = b; ba.to = a; ba.capacity = 0; ba.cost = 0;
    e++;
    ba.opposite = adj[a].size();
    adj[a].emplace_back(ab);
    adj[b].emplace_back(ba);
  }
};

struct MinCostMaxFlow { // require 'graph'
  vl potential;
  vl back; // index of edge back to source
  vvl capacity, cost; // mutable copies for every edge
  l result_cost, result_flow;

  void sssp(Graph& g, l source) {
    fill(all(potential), INF);
    fill(all(back), -1);
    vb in_queue(g.v);
    queue<l> q;
    potential[source] = 0;
    in_queue[source] = true;
    q.emplace(source);
    while (!q.empty()) {
      l u = q.front(); q.pop();
      in_queue[u] = false;
      F(i, 0, g.adj[u].size()) {
        auto& e = g.adj[u][i];
        if (capacity[u][i] == 0) continue;
        l v = e.to;
        l t = potential[u] + cost[u][i];
        if (t >= potential[v]) continue;
        potential[v] = t;
        back[v] = e.opposite;
        if (in_queue[v]) continue;
        in_queue[v] = true;
        q.emplace(v);
      }
    }
    // update costs
    F(i, 0, g.v) {
      F(j, 0, g.adj[i].size()) {
        if (capacity[i][j] == 0) continue;
        cost[i][j] += potential[g.adj[i][j].from] - potential[g.adj[i][j].to];
      }
    }
  }

  MinCostMaxFlow(Graph& g, l s, l t, l max_allowed_cost) {
    result_cost = 0;
    result_flow = 0;
    cost.resize(g.v);
    capacity.resize(g.v);
    potential.resize(g.v);
    back.resize(g.v);
    F(i, 0, g.v) {
      cost[i].resize(g.adj[i].size());
      capacity[i].resize(g.adj[i].size());
      F(j, 0, cost[i].size()) {
        cost[i][j] = g.adj[i][j].cost;
        capacity[i][j] = g.adj[i][j].capacity;
      }
    }
    while (max_allowed_cost >= 0) {
      sssp(g, s);
      if (potential[t] == INF) break;
      // augment
      stack<l> path; // from s -> t, idexes of edges
      l m = INF;
      auto u = t;
      while (back[u] != -1) {
        auto& ba = g.adj[u][back[u]];
        u = ba.to;
        path.push(ba.opposite);
        m = min(m, capacity[u][ba.opposite]);
      }
      // <- u == s
      while (!path.empty()) {
        auto e = path.top(); path.pop();
        max_allowed_cost -= m * g.adj[u][e].cost;
        if (max_allowed_cost < 0) break;
        capacity[u][e] -= m;
        l v = g.adj[u][e].to;
        l vu = g.adj[u][e].opposite;
        capacity[v][vu] += m;
        u = v;
      }
      if (max_allowed_cost >= 0) result_flow += m;
    }
    F(i, 0, g.v) {
      F(j, 0, g.adj[i].size()) {
        result_cost += (g.adj[i][j].capacity - capacity[i][j]) * g.adj[i][j].cost;
      }
    }
  }
};

class AngelDemonGame {
public:
  string winner(vector <string> G, int A, int D) {
    l N = G.size();
    {
      // angel always wins
      Graph g(N);
      F(i, 0, N) F(j, 0, N) {
        if (i == j) continue;
        if (G[i][j] == 'Y') {
          g.add_flow(i, j, 1, 0);
        } else {
          g.add_flow(i, j, 1, 1);
        }
      }
      MinCostMaxFlow mc(g, 0, N - 1, A);
      if (mc.result_flow > D) return "Angel";
    }
    {
      // daemon always wins
      Graph g(N);
      F(i, 0, N) F(j, 0, N) {
        if (i == j) continue;
        if (G[i][j] == 'Y') g.add_flow(i, j, 1, 0);
      }
      unordered_set<l> s;
      queue<l> q;
      s.emplace(0);
      q.emplace(0);
      // potential connections from 0
      while (not q.empty()) {
        auto a = q.front(); q.pop();
        for (auto e : g.adj[a]) {
          if (s.count(e.to)) continue;
          s.emplace(e.to);
          q.emplace(e.to);
        }
      }
      F(i, 0, min(A, 2)) {
        bool added = false;
        auto c = s;
        for (auto a : c) {
          unordered_set<l> t;
          t.emplace(a);
          for (auto e : g.adj[a]) t.emplace(e.to);
          F(b, 0, g.v) {
            if (t.count(b)) continue;
            g.add_flow(a, b, 1, 0);
            g.add_flow(b, a, 1, 0);
            s.emplace(b);
            added = true;
          }
        }
        if (not added) break;
      }
      MinCostMaxFlow mc(g, 0, N - 1, 0); // normal max flow
      if (mc.result_flow <= D) return "Demon";
    }
    return "Unknown";
  }
  // BEGIN CUT HERE
public:
  void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
  template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
  void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
  void test_case_0() { string Arr0[] = {"NYNY",
                                        "YNYY",
                                        "NYNN",
                                        "YYNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; string Arg3 = "Angel"; verify_case(0, Arg3, winner(Arg0, Arg1, Arg2)); }
  void test_case_1() { string Arr0[] = {"NYNY",
                                        "YNYY",
                                        "NYNN",
                                        "YYNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 6; string Arg3 = "Demon"; verify_case(1, Arg3, winner(Arg0, Arg1, Arg2)); }
  void test_case_2() { string Arr0[] = {"NNNN",
                                        "NNNN",
                                        "NNNN",
                                        "NNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; string Arg3 = "Unknown"; verify_case(2, Arg3, winner(Arg0, Arg1, Arg2)); }
  void test_case_3() { string Arr0[] = {"NYNNNY",
                                        "YNNYNN",
                                        "NNNNYN",
                                        "NYNNNN",
                                        "NNYNNN",
                                        "YNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 4; string Arg3 = "Unknown"; verify_case(3, Arg3, winner(Arg0, Arg1, Arg2)); }
  void test_case_4() { string Arr0[] = {"NYNNNY",
                                        "YNNYNN",
                                        "NNNNYN",
                                        "NYNNNN",
                                        "NNYNNN",
                                        "YNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; int Arg2 = 4; string Arg3 = "Angel"; verify_case(4, Arg3, winner(Arg0, Arg1, Arg2)); }
  void test_case_5() { string Arr0[] = {"NYNNNY",
                                        "YNNYNN",
                                        "NNNNYN",
                                        "NYNNNN",
                                        "NNYNNN",
                                        "YNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 8; string Arg3 = "Demon"; verify_case(5, Arg3, winner(Arg0, Arg1, Arg2)); }

  // END CUT HERE
  ;
};

// BEGIN CUT HERE
void solve(istream&, ostream&) {}
int main() {
  AngelDemonGame ___test;
  ___test.run_test(-1);
}
// END CUT HERE
