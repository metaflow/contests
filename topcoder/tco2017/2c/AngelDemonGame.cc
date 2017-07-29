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

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool in_queue;
  l potential;
  vector<pedge> adjusted;
  pedge back;
};

struct edge {
  pnode from, to;
  l capacity, original_capacity;
  l cost, original_cost;
  pedge opposite;
};

void connect(pnode &a, pnode &b, l w, l cost) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->capacity = ea->original_capacity = w;
  ea->cost = ea->original_cost = cost; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->capacity = eb->original_capacity = 0;
  eb->cost = eb->original_cost = 0; eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

void sssp(pnode start, graph& g) {
  for (auto u : g) {
    u->potential = INF;
    u->in_queue = false;
    u->back = NULL;
  }
  queue<pnode> q;
  start->potential = 0;
  start->in_queue = true;
  q.emplace(start);
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    u->in_queue = false;
    for (auto e : u->adjusted) {
      if (e->capacity == 0) continue;
      auto v = e->to;
      l t = u->potential + e->cost;
      if (t >= v->potential) continue;
      v->potential = t;
      v->back = e;
      if (v->in_queue) continue;
      v->in_queue = true;
      q.emplace(v);
    }
  }
  // update potentials
  for (auto u : g) {
    for (auto e : u->adjusted) {
      if (e->capacity == 0) continue;
      e->cost += e->from->potential - e->to->potential;
    }
  }
}

// TODO: move to template, try to imolement as a vectors intstead of pointers
ll min_cost_max_flow(graph& g, pnode s, pnode t, l max_cost) {
  l flow = 0;
  while (max_cost >= 0) {
    sssp(s, g);
    if (t->potential == INF) break;
    // augment
    stack<pedge> a;
    l m = INF;
    auto u = t;
    while (u->back) {
      a.push(u->back);
      m = min(m, u->back->capacity);
      u = u->back->from;
    }
    while (!a.empty()) {
      auto e = a.top(); a.pop();
      max_cost -= m * e->original_cost;
      if (max_cost < 0) break;
      e->capacity -= m;
      e->opposite->capacity += m;
    }
    if (max_cost >= 0) flow += m;
  }
  l cost = 0;
  for (auto u : g) {
    for (auto e : u->adjusted) {
      cost += (e->original_capacity - e->capacity) * e->original_cost;
    }
  }
  return make_pair(flow, cost);
}

class AngelDemonGame {
public:
  string winner(vector <string> G, int A, int D) {
    l N = G.size();
    {
      // angel always wins
      graph g(N);
      for (auto& u : g) u = make_shared<node>();
      F(i, 0, N) F(j, 0, N) {
        if (i == j) continue;
        if (G[i][j] == 'Y') {
          connect(g[i], g[j], 1, 0);
        } else {
          connect(g[i], g[j], 1, 1);
        }
      }
      ll a = min_cost_max_flow(g, g[0], g[N - 1], A);
      if (a.first > D) return "Angel";
    }
    {
      // daemon always wins
      graph g(N);
      for (auto& u : g) u = make_shared<node>();
      F(i, 0, N) F(j, 0, N) {
        if (i == j) continue;
        if (G[i][j] == 'Y') connect(g[i], g[j], 1, 0);
      }
      unordered_set<pnode> s;
      queue<pnode> q;
      s.emplace(g[0]);
      q.emplace(g[0]);
      while (not q.empty()) {
        auto a = q.front(); q.pop();
        for (auto e : a->adjusted) {
          if (s.count(e->to)) continue;
          s.emplace(e->to);
          q.emplace(e->to);
        }
      }
      F(i, 0, min(A, 2)) {
        bool added = false;
        auto c = s;
        for (auto a : c) {
          unordered_set<pnode> t;
          t.emplace(a);
          for (auto e : a->adjusted) t.emplace(e->to);
          for (auto b : g) {
            if (t.count(b)) continue;
            connect(a, b, 1, 0);
            connect(b, a, 1, 0);
            s.emplace(b);
            added = true;
          }
        }
        if (not added) break;
      }
      auto f = min_cost_max_flow(g, g[0], g[N - 1], 0);
      if ((f).first <= D) return "Demon";
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
