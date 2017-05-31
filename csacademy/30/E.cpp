#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

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

struct node;
using pnode = shared_ptr<node>;
using graph = vector<pnode>;

struct node {
  l id;
  l level = 0;
  vector<pnode> adjusted;
  pnode back;
  vector<pnode> jumps;
};

void build_lca(pnode u) {
  if (u->back) {
    l i = 0;
    u->jumps.emplace_back(u->back);
    while ((l)(u->jumps.back()->jumps.size()) > i) {
      u->jumps.emplace_back(u->jumps.back()->jumps[i]);
      i++;
    }
  }
  for (auto v : u->adjusted) {
    if (v == u->back) continue;
    v->level = u->level + 1;
    v->back = u;
    build_lca(v);
  }
}

pnode lca(pnode a, pnode b) {
  while (a->level > b->level) {
    l i = 0;
    while (i + 1 < a->jumps.size() and a->jumps[i + 1]->level >= b->level) i++;
    a = a->jumps[i];
  }
  while (b->level > a->level) {
    l i = 0;
    while (i + 1 < b->jumps.size() and b->jumps[i + 1]->level >= a->level) i++;
    b = b->jumps[i];
  }
  while (a != b) {
    l i = a->jumps.size() - 1;
    while (i > 0 and a->jumps[i] == b->jumps[i]) i--;
    a = a->jumps[i];
    b = b->jumps[i];
  }
  return a;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // solution
  l n, q;
  while (cin >> n >> q) {
    graph g(n);
    F(i, 0, n) {
      g[i] = make_shared<node>();
      g[i]->id = i + 1;
    }
    F(i, 0, n - 1) {
      l a, b; cin >> a >> b; a--; b--;
      g[a]->adjusted.emplace_back(g[b]);
      g[b]->adjusted.emplace_back(g[a]);
    }
    pnode root = g[random_in_range(0, n)];
    root->level = 0;
    build_lca(root);
    F(i, 0, q) {
      l a, b, c; cin >> a >> b >> c; a--; b--; c--;
      pnode ab = lca(g[a], g[b]);
      pnode ac = lca(g[a], g[c]);
      pnode bc = lca(g[b], g[c]);
      pnode r = lca(ab, g[c]);
      l base = (g[a]->level + g[b]->level + g[c]->level - 3 * r->level);
      pnode best = ab;
      if (ac->level > best->level) best = ac;
      if (bc->level > best->level) best = bc;
      cout << best->id << ' ' << (base - best->level + r->level) << lf;
    }
  }
}
