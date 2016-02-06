#include<bits/stdc++.h>
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

struct node;
struct edge;
using pnode = shared_ptr<node>;
using graph = vector<pnode>;

struct node {
  bool visited = false;
  vector<pnode> adjusted;
  char letter = 'x';
  l same = 0;
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    graph g(n);
    for (auto &u : g) {
      u = make_shared<node>();
    }
    for (l i = 0; i < m; i++) {
      l a, b; cin >> a >> b; a--; b--;
      g[a]->adjusted.push_back(g[b]);
      g[b]->adjusted.push_back(g[a]);
    }
    bool ok = true;
    for (auto u : g) {
      if (u->adjusted.size() == n - 1) {
        u->letter = 'b';
        u->visited = true;
      }
    }
    char x = 'a';
    for (auto u : g) {
      if (u->visited) continue;
      if (x == 'x') {
        ok = false;
        break;
      }
      queue<pnode> q;
      q.emplace(u);
      l marked = 0;
      u->visited = true;
      u->letter = x;
      marked++;
      while (!q.empty()) {
        auto v = q.front(); q.pop();
        for (auto r : v->adjusted) {
          if (!r->visited || r->letter == v->letter) v->same++;
          if (r->visited) continue;
          r->visited = true;
          r->letter = x;
          marked++;
          q.emplace(r);
        }
      }
      for (auto v : g) {
        if (v->letter != x) continue;
        if (v->same != marked - 1) ok = false;
      }
      if (!ok) break;
      if (x == 'a') { x = 'c'; } else { x = 'x'; }
    }
    if (ok) {
      cout << "Yes" << endl;
      for (auto u : g) cout << u->letter;
      cout << endl;
    } else {
      cout << "No" << endl;
    }
  }
}

