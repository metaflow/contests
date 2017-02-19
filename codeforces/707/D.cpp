#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

struct node;
using pnode = shared_ptr<node>;
struct edge { l op, a, b; pnode to; };
struct node {
  vl ids;
  vector<edge> children;
  edge back;
};

l apply(const edge& e, vvb& bc, vl& ss, l& total) {
  switch (e.op) {
  case 0: return 0;
  case 1: if (bc[e.a][e.b]) return 0;
    bc[e.a][e.b] = true;
    ss[e.a]++;
    total++;
    return 2;
  case 2: if (not bc[e.a][e.b]) return 0;
    bc[e.a][e.b] = false;
    ss[e.a]--;
    total--;
    return 1;
  case 3:
    bc[e.a].flip();
    l t = bc[e.a].size() - ss[e.a];
    total += t - ss[e.a];
    ss[e.a] = t;
    return 3;
  }
  assert(false);
  return 0;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m, q;
  while (cin >> n >> m >> q) {
    vvb bc(n, vb(m));
    vl shelfes(n);
    l total = 0;
    vl answers(q);
    vector<pnode> history(q);
    pnode current = make_shared<node>();
    history[0] = current; // for q = 0
    for (l i = 0; i < q; i++) {
      history[i] = current;
      l op, a, b = 0;
      cin >> op >> a;
      if (op < 3) { cin >> b; b--; }
      if (op == 4) {
        current = history[a];
      } else {
        a--;
        pnode next = make_shared<node>();
        edge e;
        e.op = op; e.a = a; e.b = b;
        e.to = next;
        current->children.emplace_back(e);
        current = next;
      }
      current->ids.emplace_back(i);
    }
    current = history[0];
    while (true) {
      if (current->children.empty()) {
        for (auto id : current->ids) answers[id] = total;
        if (current == history[0]) break;
        apply(current->back, bc, shelfes, total);
        current = current->back.to;
        continue;
      }
      auto e = current->children.back(); current->children.pop_back();
      auto next = e.to;
      next->back.to = current;
      next->back.op = apply(e, bc, shelfes, total);
      next->back.a = e.a; next->back.b = e.b;
      current = next;
    }
    for (auto i : answers) cout << i << '\n';
  }
}
