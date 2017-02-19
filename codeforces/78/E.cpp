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

l n;

l linear(l t, l r, l c) {
  return t * n * n + r * n + c;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l T;
  while (cin >> n >> T) {
    vector<string> lab(n);
    vector<pnode> g((T + 1) * n * n + 2);
    for (auto& u : g) u = make_shared<node>();
    auto source = g[linear(T, n-1, n-1) + 1];
    auto sink = g[linear(T, n-1, n-1) + 2];
    vector<ll> z;
    for (l r = 0; r < n; r++) {
      cin >> lab[r];
      for (l c = 0; c < n; c++) {
        if (lab[r][c] == 'Y') continue;
        if (lab[r][c] == 'Z') {
          z.emplace_back(r, c);
          continue;
        }
        connect(source, g[linear(0, r, c)], lab[r][c] - '0');
        lab[r][c] = '0';
      }
    }
    for (l r = 0; r < n; r++) {
      string row; cin >> row;
      for (l c = 0; c < n; c++) {
        if (row[c] == 'Y' or row[c] == 'Z') continue;
        connect(g[linear(T, r, c)], sink, row[c] - '0');
      }
    }
    const l dr[] = {1, 0, -1, 0};
    const l dc[] = {0, 1, 0, -1};
    for (l t = 0; t < T; t++) {
      // connect corridors
      for (l r = 0; r < n; r++) {
        for (l c = 0; c < n; c++) {
          connect(g[linear(t, r, c)], g[linear(t + 1, r, c)], INF);
          if (lab[r][c] != '0') continue;
          for (l d = 0; d < 4; d++) {
            l r_ = r + dr[d];
            l c_ = c + dc[d];
            if (r_ < 0 or r_ >= n or c_ < 0 or c_ >= n or lab[r_][c_] != '0')
              continue;
            connect(g[linear(t, r, c)], g[linear(t + 1, r_, c_)], INF);
          }
        }
      }
      // spread
      vll z_;
      for (auto e : z) {
        l r, c; tie(r, c) = e;
        for (l d = 0; d < 4; d++) {
          l r_ = r + dr[d];
          l c_ = c + dc[d];
          if (r_ < 0 or r_ >= n or c_ < 0 or c_ >= n or lab[r_][c_] != '0')
            continue;
          z_.emplace_back(r_, c_);
          lab[r_][c_] = 'Z';
        }
      }
      swap(z_, z);
    }
    cout << max_flow(g, source, sink) << '\n';
  }
}
