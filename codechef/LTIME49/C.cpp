#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "C"
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
  l id, club, level, depth, value;
  bool visited;
  vector<pnode> adjusted;
  vector<pnode> adjusted_club;
  vector<pnode> adjusted_good;
  pnode parent;
};

void dfs_clubs(pnode r, vector<pnode>& anc, vector<pnode>& subclub_heads) {
  auto h = anc[r->club];
  if (h) {
    h->adjusted_club.emplace_back(r);
  } else {
    subclub_heads.emplace_back(r);
  }
  anc[r->club] = r;
  for (auto u : r->adjusted) dfs_clubs(u, anc, subclub_heads);
  anc[r->club] = h;
}

void dfs_depth(pnode r) {
  r->depth = 0;
  for (auto u : r->adjusted_club) {
    dfs_depth(u);
    r->depth = max(r->depth, u->depth + 1);
  }
}

const l MOD = e9 + 7;

void dfs_count(pnode r, vector<pnode>& uplink) {
  pnode up;
  if (r->level <= r->depth) {
    up = uplink[r->level];
    uplink[r->level] = r;
    if (uplink[r->level + 1]) {
      uplink[r->level + 1]->adjusted_good.emplace_back(r);
    }
  }
  r->value = 0;
  for (auto u : r->adjusted_club) {
    dfs_count(u, uplink);
  }
  if (r->level == 0) {
    r->value = 1;
  } else {
    for (auto u : r->adjusted_good) {
      r->value = (r->value + u->value) % MOD;
    }
  }
  if (r->level <= r->depth) {
    if (up and r->level) {
      up->value = (up->value + r->value) % MOD;
    }
    uplink[r->level] = up;
  }
}

void solve(istream& cin, ostream& cout) {
  l tcc; cin >> tcc;
  while (tcc--) {
    l n, m; cin >> n >> m;
    graph g(n);
    for (auto& u : g) u = make_shared<node>();
    F(i, 1, n) {
      l p; cin >> p;
      g[p]->adjusted.emplace_back(g[i]);
      g[i]->parent = g[p];
    }
    F(i, 0, n) cin >> g[i]->club;
    F(i, 0, n) cin >> g[i]->level;
    vector<pnode> subclub_heads;
    vector<pnode> anc(n);
    dfs_clubs(g[0], anc, subclub_heads);
    for (auto h : subclub_heads) dfs_depth(h);
    for (auto h : subclub_heads) {
      vector<pnode> uplink(h->depth + 2);
      dfs_count(h, uplink);
    }
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
