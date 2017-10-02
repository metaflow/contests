#if defined(LOCAL)
#define PROBLEM_NAME "#PROBLEM_NAME"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
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
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

struct Edge {
  l to;
  l id, from;
  l opposite; // for flow, index in 'to'
  l capacity; // for flow
  l cost;
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

struct MaxFlow {  // require 'graph'
  l result_flow;
  vl age;
  vl back;
  vvl capacity;

  MaxFlow(Graph& g, l source, l sink) {
    result_flow = 0;
    age.resize(g.v);
    back.resize(g.v);
    capacity.resize(g.v);
    F(i, 0, g.v) {
      capacity[i].resize(g.adj[i].size());
      F(j, 0, g.adj[i].size()) capacity[i][j] = g.adj[i][j].capacity;
    }
    while (true) {
      fill(all(age), 0);
      fill(all(back), -1);
      queue<l> q;
      q.push(source); age[source] = 1;
      while (not (q.empty() || age[sink])) {
        l u = q.front(); q.pop();
        F(j, 0, g.adj[u].size()) {
          auto& e = g.adj[u][j];
          l v = e.to;
          if (age[v] || capacity[u][j] == 0) continue;
          back[v] = e.opposite;
          age[v] = age[u] + 1;
          q.push(v);
        }
      }
      if (age[sink] == 0) break; // unreachable
      for (auto& e : g.adj[sink]) {
        l u = e.to;
        if (age[u] != age[sink] - 1 or capacity[u][e.opposite] == 0) continue;
        vll path;
        path.emplace_back(u, e.opposite);
        while (back[u] != -1) {
          auto& uv = g.adj[u][back[u]];
          u = uv.to;
          path.emplace_back(u, uv.opposite);
        }
        // adjust path
        l d = INF;
        for (auto p : path) d = min(d, capacity[p.first][p.second]);
        for (auto p : path) {
          capacity[p.first][p.second] -= d;
          auto& t = g.adj[p.first][p.second];
          capacity[t.to][t.opposite] += d;
        }
        result_flow += d;
      }
    }
  }
};


class Apocalypse {
public:
  int maximalSurvival(vector <int> p, vector <int> position, int t) {
    l n = p.size() + 1;
    Graph g(t * 2 * n + n + 2);
    Graph q(n);
    F(i, 0, n - 1) q.add_undirected(i + 1, p[i]);
    l source = g.v - 1;
    l sink = g.v - 2;
    F(i, 0, t) {
      l f = i * n * 2;
      l m = f + n;
      l e = m + n;
      F(j, 0, n) {
        g.add_flow(f + j, m + j, 1, 0);
        for (auto a : q.adj[j]) g.add_flow(f + j, m + a.to, 1, 0);
        g.add_flow(m + j, e + j, 1, 0);
      }
    }
    l e = t * 2 * n;
    vb bomb(n);
    for (auto i : position) bomb[i] = true;
    F(i, 0, n) {
      if (bomb[i]) {
        g.add_flow(source, i, 1, 0);
      } else {
        g.add_flow(e + i, sink, 1, 0);
      }
    }
    MaxFlow mf(g, source, sink);
    return mf.result_flow;
  }

  // BEGIN CUT HERE
public:
  void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
private:
  template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
  void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
  void test_case_0() { int Arr0[] = {0,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(0, Arg3, maximalSurvival(Arg0, Arg1, Arg2)); }
  void test_case_1() { int Arr0[] = {0,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 2; verify_case(1, Arg3, maximalSurvival(Arg0, Arg1, Arg2)); }
  void test_case_2() { int Arr0[] = {0,0,0,1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 3; verify_case(2, Arg3, maximalSurvival(Arg0, Arg1, Arg2)); }
  void test_case_3() { int Arr0[] = {0,1,2,3,4,5,6,7,8,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,2,3,4,5,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 50; int Arg3 = 4; verify_case(3, Arg3, maximalSurvival(Arg0, Arg1, Arg2)); }
  void test_case_4() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 0; verify_case(4, Arg3, maximalSurvival(Arg0, Arg1, Arg2)); }
  void test_case_5() { int Arr0[] = {0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(5, Arg3, maximalSurvival(Arg0, Arg1, Arg2)); }

  // END CUT HERE
  ;
};

// BEGIN CUT HERE
void solve(istream&, ostream&) {}
int main() {
  Apocalypse ___test;
  ___test.run_test(-1);
}
// END CUT HERE
