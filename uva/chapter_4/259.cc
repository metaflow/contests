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
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;

struct node {
  vector<pedge> edges;
  char name;
  pedge back;
  bool visited;
};

struct edge {
  pedge opp;
  int f;
  pnode from, to;
};

map<char, pnode> G;

void connect(pnode a, pnode b, int v) {
  auto ea = make_shared<edge>();
  auto eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->f = v; ea->opp = eb;
  eb->from = b; eb->to = a; eb->f = 0; eb->opp = ea;
  a->edges.push_back(ea);
  b->edges.push_back(eb);
}

int augment(pedge e, int d) {
  if (e) {
    d = augment(e->from->back, min(e->f, d));
    e->f -= d;
    e->opp->f += d;
  }
  return d;
}

int max_flow(pnode source, pnode sink) {
  int r = 0;

  while (true) {
    for (auto u : G) u.second->visited = false;
    queue<pnode> q;
    q.push(source); source->visited = true;
    while (!q.empty()) {
      auto u = q.front(); q.pop();
      for (auto e : u->edges) {
        auto v = e->to;
        if (e->f == 0 || v->visited) continue;
        v->back = e;
        q.push(v); v->visited = true;
      }
    }
    if (!sink->visited) break;
    r += augment(sink->back, INF);
  }

  return r;
}

int main() {
  string s;
  while (getline(cin, s)) {
    G.clear();
    G['<'] = make_shared<node>();
    G['<']->name = '<';
    G['>'] = make_shared<node>();
    G['>']->name = '_';
    for (char c = '0'; c <= '9'; c++) {
      G[c] = make_shared<node>();
      G[c]->name = c;
      connect(G[c], G['>'], 1);
    }
    int sum = 0;
    while (s != "") {
      stringstream ss(s);
      ss >> s;
      auto a = G[s[0]] = make_shared<node>();
      a->name = s[0];
      int f = s[1] - '0';
      sum += f;
      connect(G['<'], a, f);
      ss >> s;
      for (auto c : s) {
        if (c == ';') break;
        connect(a, G[c], 1);
      }
      getline(cin, s);
    }
    if (max_flow(G['<'], G['>']) == sum) {
      for (char c = '0'; c <= '9'; c++) {
        for (auto e : G[c]->edges) {
          if (e->f == 0) continue;
          cout << e->to->name;
        }
      }
      cout << endl;
    } else {
      cout << "!" << endl;
    }
  }
}
