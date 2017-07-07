#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "D"
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

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  l id, value;
  bool visited;
  vector<pnode> adjusted;
  // l subtreeSize = 1; bool blocked;
  // l level;
  // vector<pnode> up;
  vl operations;
};

struct edge {
  pnode from, to;
  l value;
};

void dfs(pnode r, unordered_set<l>& s) {
  vl back;
  for (auto x : r->operations) {
    if (x > 0 and s.count(x) == 0) {
      back.emplace_back(-x);
      s.insert(x);
    }
    if (x < 0 and s.count(-x) != 0) {
      back.emplace_back(-x);
      s.erase(-x);
    }
  }
  r->value = s.size();
  for (auto u : r->adjusted) dfs(u, s);
  for (auto x : back) {
    if (x > 0) {
      s.insert(x);
    }
    if (x < 0) {
      s.erase(-x);
    }
  }
}

void solve(istream& cin, ostream& cout) {
  l n;
  while (cin >> n) {
    graph g(n);
    for (auto& u : g) u = make_shared<node>();
    F(i, 0, n - 1) {
      l a; cin >> a; a--;
      g[a]->adjusted.emplace_back(g[i + 1]);
    }
    F(i, 0, n) {
      l k; cin >> k;
      F(j, 0, k) {
        l x; cin >> x;
        g[i]->operations.emplace_back(x);
      }
    }
    unordered_set<l> s;
    dfs(g[0], s);
    for (auto u : g) cout << u->value << lf;
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
