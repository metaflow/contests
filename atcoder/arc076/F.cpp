#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "F"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

// v max flow
struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  int age;
  vector<pedge> adjusted;
  pedge back;
};

struct edge {
  pnode from, to;
  int flow;
  pedge opposite;
};

int adjust(pedge e, int d) {
  if (!e) return d;
  d = adjust(e->from->back, min(d, e->flow));
  e->flow -= d;
  e->opposite->flow += d;
  return d;
}

void connect(pnode &a, pnode &b, int w) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->flow = w; ea->opposite = eb;
  eb->from = b; eb->to = a; eb->flow = 0; eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

int max_flow(vector<pnode> &g, pnode &source, pnode &sink) {
  int result = 0;
  while (true) {
    for (auto u : g) u->age = 0;
    queue<pnode> q;
    q.push(source); source->age = 1;
    while (!(q.empty() || sink->age != 0)) {
      auto u = q.front(); q.pop();
      for (auto e : u->adjusted) {
        auto v = e->to;
        if (v->age != 0 || e->flow == 0) continue;
        v->back = e;
        v->age = u->age + 1;
        q.push(v);
      }
    }
    if (sink->age == 0) break;
    for (auto e : sink->adjusted) {
      auto o = e->opposite;
      if (o->from->age != sink->age - 1 || o->flow == 0) continue;
      result += adjust(o, o->flow);
    }
  }
  return result;
} // ^ max flow 


void solve(istream& cin, ostream& cout) {
  l N, M;
  while (cin >> N >> M) {
    graph to_left(M), to_right(M);
    pnode source = make_shared<node>();
    pnode sink = make_shared<node>();
    F(i, 0, M) {
      to_left[i] = make_shared<node>();
      connect(to_left[i], sink, 1);
      if (i) connect(to_left[i], to_left[i - 1], N);
    }
    F(i, 0, M) {
      to_right[i] = make_shared<node>();
      connect(to_right[i], sink, 1);
    }
    F(i, 0, M - 1) connect(to_right[i], to_right[i + 1], N);
    graph g;
    g.emplace_back(source);
    g.emplace_back(sink);
    F(i, 0, N) {
      l L, R; cin >> L >> R; L--; R--;
      pnode u = make_shared<node>();
      connect(source, u, 1);
      if (L >= 0) connect(u, to_left[L], 1);
      if (R < M) connect(u, to_right[R], 1);
      g.emplace_back(u);
    }
    for (auto u : to_left) g.emplace_back(u);
    for (auto u : to_right) g.emplace_back(u);
    cout << N - max_flow(g, source, sink) << lf;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
