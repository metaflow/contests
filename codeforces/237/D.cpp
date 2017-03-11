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
const l e0 = 1, e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  l id;
  vector<edge> adjusted;
};

struct edge {
  pnode from, to;
  l id;
};

edge connect(pnode &a, pnode &b, l id) {
  edge ea, eb;
  ea.from = a; ea.to = b; ea.id = id;
  eb.from = b; eb.to = a; eb.id = id;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
  return ea;
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    graph g(n);
    for (l i = 0; i < n; i++) {
      g[i] = make_shared<node>();
      g[i]->id = i + 1;
    }
    vector<edge> E;
    for (l i = 0; i < n - 1; i++) {
      l a, b; cin >> a >> b; a--; b--;
      E.emplace_back(connect(g[a], g[b], i + 1));
    }
    vll T; // edges of T
    pnode x;
    for (auto u : g) if (u->adjusted.size() == 1) { x = u; break; }
    queue<edge> q;
    q.emplace(x->adjusted.back());
    while (not q.empty()) {
      auto e = q.front(); q.pop();
      for (auto y : e.to->adjusted) {
        if (y.to == e.from) continue;
        T.emplace_back(e.id, y.id);
        q.emplace(y);
      }
    }
    cout << n - 1 << '\n';
    for (auto u : E) cout << "2 " << u.from->id << ' ' << u.to->id << '\n';
    for (auto e : T) cout << e.first << ' ' << e.second << '\n';
  }
}
