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

template <typename Iterator>
ostream& print_range(ostream& s, const Iterator a, const Iterator b) {
  bool first = true;
  for (auto i = a; i != b; i++) {
    if (!first) s << " ";
    first = false;
    s << *i;
  }
  return s;
}


struct node;
struct edge;
using pnode = shared_pointer<node>;
using pedge = shared_pointer<edge>;
struct node {
  bool visited;
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
    for (auto u : g) u->visited = false;
    queue<pnode> q;
    q.push(source); source->visited = true;
    while (!(q.empty() || sink->visited)) {
      auto u = q.front(); q.pop();
      for (auto e : u->adjusted) {
        auto v = e->to;
        if (v->visited || e->flow == 0) continue;
        v->back = e;
        v->visited = true;
        q.push(v);
      }
    }
    if (!sink->visited) break;
    for (auto e : sink->adjusted) {
      auto o = e->opposite;
      if (!o->from->visited || o->flow == 0) continue;
      result += adjust(o, o->flow);
    }
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll answer = 0;
    int n; cin >> n;
    map<string, vector<int>> word_line;
    string s;
    getline(cin, s);
    for (int i = 0; i < n; i++) {
      getline(cin, s);
      stringstream ss(s);
      string w;
      while (ss >> w) {
        if (word_line[w].empty() || word_line[w].back() != i) {
          word_line[w].emplace_back(i);
        }
      }
    }
    vector<pnode> g;
    for (int i = 0; i < n; i++) {
      g.emplace_back();
    }
    // for (auto e : word_line) {
    //   cout << e.first << " ";
    //   print_range(cout, e.second.begin(), e.second.end()) << endl;
    // }
    // continue;
    ll best = INF;
    for (int i = 0; i < (1 << (n - 2)); i++) {
      int a = (i << 2) + 1;
      ll c = 0;
      for (auto e : word_line) {
        bool f = a & (1 << (e.second[0]));
        for (auto l : e.second) {
          if (f != bool(a & (1 << l))) {
            c++;
            break;
          }
        }
        if (c > best) break;
      }
      best = min(best, c);
    }
    cout << "Case #" << tc << ": " << best << endl;
  }
}
