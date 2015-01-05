#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct node;
const int MOD = 1000000007;

using pnode = shared_ptr<node>;

struct node {
  int a;
  bool active = false;
  bool counted = false;
  llu count;
  vector<pnode> adjusted;
};

llu count_node(pnode u, vector<pnode> &G, int d) {
  // root has smallest value
  for (auto v : G) {
    v->active = false;
    v->count = 0;
  }
  u->counted = true;
  queue<pnode> q;
  stack<pnode> s;
  q.emplace(u);
  while (!q.empty()) {
    auto v = q.front(); q.pop();
    s.emplace(v);
    for (auto t : v->adjusted) {
      if (t->active) continue;
      if (t->a < u->a) continue;
      if (t->a > u->a + d) continue;
      if (t->counted && t->a == u->a) continue;
      t->active = true;
      q.emplace(t);
    }
  }
  while (!s.empty()) {
    auto v = s.top(); s.pop();
    v->count = 1;
    for (auto t : v->adjusted) {
      v->count *= (t->count + 1);
      v->count %= MOD;
    }
  }
  return u->count;
}

int main() {
  int d, n;
  while (cin >> d >> n) {
    vector<pnode> G(n);
    for (auto &v : G) v = make_shared<node>();
    for (int i = 0; i < n; i++) cin >> (G[i]->a);
    for (int i = 0; i < n - 1; i++) {
      int a, b;
      cin >> a >> b; a--; b--;
      G[a]->adjusted.emplace_back(G[b]);
      G[b]->adjusted.emplace_back(G[a]);
    }
    llu count = 0;
    for (auto u : G) {
      count += count_node(u, G, d);
      count %= MOD;
    }
    cout << count << endl;
  }
}
