#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool visited;
  vector<pedge> adjusted;
  pedge back;
  int below = 0;
};

struct edge {
  pnode from, to;
  int w;
  double p;
};

pedge connect(pnode &a, pnode &b, int w) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->w = w; ea->from = a; ea->to = b;
  eb->w = w; eb->from = b; eb->to = a;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
  return ea;
}

int n;

double prob(const pedge e) {
  double k = min(e->to->below, e->from->below);
  double a = (n - k) * k;
  double c = (double)n * (double)(n - 1);
  return 3 * a / c;
}

void dfs(pnode &u) {
  u->visited = true;
  u->below = 1;
  for (auto e : u->adjusted) {
    if (e->to->visited) continue;
    dfs(e->to);
    u->below += e->to->below;
  }
}

int main() {
  while (cin >> n) {
    graph g(n);
    for (int i = 0; i < n; i++) g[i] = make_shared<node>();
    vector<pedge> edges;
    for (int i = 0; i < n - 1; i++) {
      int f, t, w;
      cin >> f >> t >> w;
      f--; t--;
      edges.emplace_back(connect(g[f], g[t], w));
    }
    double l = 0;
    dfs(g[0]);
    double c = 6 / ((double)n * (double)(n - 1));
    for (auto e : edges) {
      double k = min(e->to->below, e->from->below);
      e->p = k * (n - k);
      l += e->p * e->w;
    }
    int q;
    cin >> q;
    while (q--) {
      int i, w;
      cin >> i >> w;
      i--;
      l -= (edges[i]->w - w) * edges[i]->p;
      printf("%.9f\n", l * c);
      edges[i]->w = w;
    }
  }
}
