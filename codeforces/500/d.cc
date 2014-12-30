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
};

struct edge {
  pnode from, to;
  int to_count;
  //pedge opposite;
  int w;
  double p;
};

pedge connect(pnode &a, pnode &b, int w) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->w = w; ea->to_count = -1; ea->from = a; ea->to = b;// ea->opposite = eb;
  eb->w = w; eb->to_count = -1; eb->from = b; eb->to = a;// eb->opposite = ea;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
  return ea;
}

int n;

void count(const pedge e) {
  if (e->to_count != -1) return;
  e->to_count = 1;
  for (auto f : e->to->adjusted) {
    if (f->to == e->from) continue;
    count(f);
    e->to_count += f->to_count;
  }
}

double prob(const pedge e) {
  int k = e->to_count;
  double a = (double)(n - k) * (double)(n - k - 1) * (n - k - 2);
  double b = (double)k * (double)(k - 1) * (double)(k - 2);
  double c = (double)n * (double)(n - 1) * (double)(n - 2);
  return 1 - (a + b) / c;
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
    for (auto e : edges) {
      count(e);
      e->p = prob(e);
      l += e->p * e->w;
    }
    int q;
    cin >> q;
    while (q--) {
      int i, w;
      cin >> i >> w;
      i--;
      l -= (edges[i]->w - w) * edges[i]->p;
      printf("%.9f\n", 2 * l);
      edges[i]->w = w;
    }
  }
}
