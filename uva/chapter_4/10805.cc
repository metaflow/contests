#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct node;
using pnode = shared_ptr<node>;
using graph = vector<pnode>;

struct node {
  int age;
  bool visited;
  graph adjusted;
  graph tree;
  int idx;
};

pnode furthest(pnode s, graph &g) {
  for (auto u : g) u->visited = false;
  queue<pnode> q;
  q.push(s); s->visited = true; s->age = 0;
  auto u = s;
  while (!q.empty()) {
    u = q.front(); q.pop();
    for (auto v : u->tree) {
      if (v->visited) continue;
      v->visited = true;
      v->age = u->age + 1;
      q.push(v);
    }
  }
  return u;
}

int test(pnode c1, pnode c2, graph &g) {
  for (auto u : g) u->tree.clear();
  for (auto u : g) {
    u->visited = false;
    u->tree.clear();
  }
  queue<pnode> q;
  q.push(c1); c1->visited = true;
  if (c1 != c2) {
    q.push(c2); c2->visited = true;
    c1->tree.push_back(c2);
    c2->tree.push_back(c1);
  }
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    for (auto v : u->adjusted) {
      if (v->visited) continue;
      v->visited = true;
      v->tree.push_back(u);
      u->tree.push_back(v);
      q.push(v);
    }
  }
  return furthest(furthest(c1, g), g)->age;
}

int solve(graph &g) {
  int best = INF;
  if (g.empty()) best = 0;
  for (auto u : g) {
    best = min(best, test(u, u, g));
    for (auto v : u->adjusted) {
      if (v->idx > u->idx) continue;
      best = min(best, test(u, v, g));
    }
  }
  return best;
}

int main() {
  int tcc, i, j, n, m, tc;
  cin >> tcc;
  for (tc = 1; tc <= tcc; tc++) {
    cin >> n >> m;
    graph g(n);
    i = 0;
    for (auto &u : g) {
      u = make_shared<node>();
      u->idx = i++;
    }
    while (m--) {
      cin >> i >> j;
      g[i]->adjusted.push_back(g[j]);
      g[j]->adjusted.push_back(g[i]);
    }
    cout << "Case #" << tc << ":\n" << solve(g) << endl << endl;
  }
  return 0;
}

// bruteforce testing

int back(int i, graph &g) {
  auto u = g[i];
  if (i == 0) {
    u = furthest(u, g);
    for (auto u : g) if (!u->visited) return INF;
    return furthest(u, g)->age;
  }
  int best = INF;
  for (auto v : u->adjusted) {
    u->tree.push_back(v);
    v->tree.push_back(u);
    best = min(best, back(i - 1, g));
    u->tree.pop_back();
    v->tree.pop_back();
  }
  return best;
}

int brute(graph &g) {
  for (auto u : g) u->tree.clear();
  for (auto u : g) u->visited = false;
  return back(g.size() - 1, g);
}


bool connected(graph &g) {
  for (auto u : g) u->visited = false;
  queue<pnode> q;
  q.push(g[0]); g[0]->visited = true;
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    for (auto v : u->adjusted) {
      if (v->visited) continue;
      v->visited = true;
      q.push(v);
    }
  }
  for (auto u : g) if (!u->visited) return false;
  return true;
}

int main_test() {
  int i, j, n, m;
  auto seed = time(NULL);
  srand(1412946814);
  i = 0;
  while (i < 1000) {
    n = rand() % 7 + 2;
    m = rand() % (n * (n - 1) / 2);
    // cerr << n << " " << m << endl;
    graph g(n);
    for (auto &u : g) u = make_shared<node>();
    set<ii> p;
    j = 0;
    while (j < m) {
      ii e(rand() % n, rand() % n);
      if (e.first >= e.second) continue;
      if (p.count(e) != 0) continue;
      p.insert(e);
      g[e.first]->adjusted.push_back(g[e.second]);
      g[e.second]->adjusted.push_back(g[e.first]);
      j++;
    }
    if (!connected(g)) continue;
    cerr << ".";
    i++;
    int a = solve(g);
    int b = brute(g);
    if (a == b) continue;
    cout << "FAILED " << a << " " << b << " " << seed << endl;
    cout << n << " " << m << endl;
    for (auto e : p) {
      cout << e.first << " " << e.second << endl;
    }
    return 0;
  }
  cout << "OK" << endl;
  return 0;
}


