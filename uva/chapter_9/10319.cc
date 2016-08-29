#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  bool visited;
  bool in_stack;
  int age, reachable;
  vector<pedge> forward;
  pnode negate;
  //vector<pedge> backward;
};

struct edge {
  pnode from, to;
};

void connect(pnode a, pnode b) {
  pedge e = make_shared<edge>();
  e->from = a; e->to = b;
  a->forward.emplace_back(e);
  //b->backward.emplace_back(e);
}

bool scc_dfs(pnode u, int& age, stack<pnode>& s) {
  age++;
  u->age = u->reachable = age;
  u->visited = true;
  s.push(u);
  u->in_stack = true;
  for (auto e : u->forward) {
    auto v = e->to;
    if (!v->visited) scc_dfs(v, age, s);
    if (v->in_stack) u->reachable = min(u->reachable, v->reachable);
  }
  if (u->age == u->reachable) {
    while (true) {
      auto v = s.top(); s.pop();
      if (v->negate->reachable == v->reachable) return true;
      v->in_stack = false;
      if (u == v) break;
    }
  }
  return false;
}

bool find_scc(graph& g) {
  int age = 0;
  for (auto u : g) {
    if (u->visited) continue;
    stack<pnode> s;
    if (scc_dfs(u, age, s)) return true;
  }
  return false;
}

graph sat;

void disjunction(int a, int b) {
  connect(sat[a ^ 1], sat[b]);
  connect(sat[b ^ 1], sat[a]);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll s, a, m; cin >> s >> a >> m;
    sat.clear();
    sat.resize((s + a) * 2);
    for (auto &u : sat) u = make_shared<node>();
    for (size_t i = 0; i < sat.size(); i++) {
      sat[i]->negate = sat[i ^ 1];
      sat[i]->visited = false;
    }
    for (ll i = 0; i < m; i++) {
      ll s1, s2, a1, a2;
      cin >> s1 >> a1 >> s2 >> a2;
      s1 = (s1 - 1) * 2;
      s2 = (s2 - 1) * 2;
      a1 = (a1 - 1 + s) * 2;
      a2 = (a2 - 1 + s) * 2;
      if (s1 > s2) {
        a1 = a1 ^ 1;
        a2 = a2 ^ 1;
      }
      if (a1 > a2) {
        s1 = s1 ^ 1;
        s2 = s2 ^ 1;
      }
      if (a1 == a2) {
        disjunction(a1, s1);
        disjunction(a1, s1 ^ 1);
      } else if (s1 == s2) {
        disjunction(s1, a1);
        disjunction(s1, a1 ^ 1);
      } else {
        disjunction(a1, s1);
        disjunction(a1, a2);
        disjunction(s2, s1);
        disjunction(s2, a2);
      }
    }
    if (find_scc(sat)) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  }
}

