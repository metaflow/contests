#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct node;
using pnode = shared_ptr<node>();

struct node {
  bool in_set = false;
  vector<int> adjusted;
  vector<int> h;
  int a = INF;
  int t = INF;
};

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int V, E;

    cin >> V >> E;
    vector<node> g(V);

    for (int i = 0; i < E; i++) {
      int x, y, h;
      cin >> x >> y >> h; x--; y--;
      g[x].adjusted.emplace_back(y);
      g[x].h.emplace_back(h);
      g[y].adjusted.emplace_back(x);
      g[y].h.emplace_back(h);
    }

    queue<int> q;
    vector<bool> in_queue(V);
    q.emplace(0); g[0].a = 0; in_queue[0] = true;
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      in_queue[u] = false;
      for (int i = 0; i < g[u].adjusted.size(); i++) {
        int v = g[u].adjusted[i];
        if (g[v].a > g[u].a + g[u].h[i]) {
          g[v].a = g[u].a + g[u].h[i];
          if (in_queue[v]) continue;
          q.emplace(v); in_queue[v] = true;
        }
      }
    }

    for (auto u : g) {
      cerr << "*" << u.a << endl;
    }

    vector<int> d(V);
    for (int i = 0; i < V; i++) d[i] = i;
    sort(d.begin(), d.end(), [g] (const int &a, const int &b) {
      return g[a].a < g[b].a;
    });

    int m = 0;
    int t = 0;
    int h = 0;
    for (auto i : d) {
      t += (g[i].a - h) * m;
      g[i].t = t;
      m++;
      h = g[i].a;
    }

    printf("Case #%d:\n", tc);
    for (int i = 0; i < V; i++) {
      if (i) printf(" ");
      printf("%d", g[i].t);
    }
    printf("\n");
  }
}
