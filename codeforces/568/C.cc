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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

struct node;
struct edge;
using pnode = shared_ptr<node>;
using graph = vector<pnode>;

struct node {
  ll pos;
  int type;
  bool visited;
  vi possible;
  vector<pnode> adjusted;
};

struct edge {
  pnode from, to;
};

int get_letter(vi& az, int from, int type) {
  for (ll i = from; i < (ll)az.size(); i++) {
    if (az[i] == type) return i;
  }
  return -1;
}

vi get_possible(vi current, pnode from, graph& g) {
  for (auto u : g) u->visited = false;
  queue<pnode> q;
  current[from->pos] &= from->type;
  from->visited = true;
  q.emplace(from);
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    for (auto v : u->adjusted) {
      if (v->visited) continue;
      current[v->pos] &= v->type;
      v->visited = true;
      q.emplace(v);
    }
  }
  return current;
}

bool valid(vi& possible) {
  for (auto i : possible) if (i == 0) return false;
  return true;
}

bool solve(size_t pos, vi& types, vi possible, vi& values, graph& g);

bool check(size_t pos, vi& types, vi possible, vi& values, graph& g) {
  if (types[values[pos]] & possible[pos]) {
    vi m(possible.begin(), possible.end());
    auto u = g[pos * 2 + types[values[pos]] - 1];
    for (ll i = 0; i < m.size(); i++) m[i] = m[i] & u->possible[i];
    // auto m = get_possible(possible, g[pos * 2 + types[values[pos]] - 1], g);
    if (valid(m) && solve(pos + 1, types, m, values, g)) return true;
  }
  return false;
}

bool solve(size_t pos, vi& types, vi possible, vi& values, graph& g) {
  if (pos >= values.size()) return true;

  if (check(pos, types, possible, values, g)) return true;

  values[pos]++;
  if (values[pos] >= (ll)types.size()) return false;
  for (size_t i = pos + 1; i < values.size(); i++) values[i] = 0;
  if (check(pos, types, possible, values, g)) return true;

  values[pos] = get_letter(types, values[pos], 3 - types[values[pos]]);
  if (values[pos] == -1) return false;
  for (size_t i = pos + 1; i < values.size(); i++) values[i] = 0;
  if (check(pos, types, possible, values, g)) return true;
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string VC;
  while (cin >> VC) {
    vi types(VC.size());
    int y = 0;
    for (size_t i = 0; i < types.size(); i++) {
      types[i] = (VC[i] == 'V' ? 1 : 2);
      y = y | types[i];
    }
    ll n, m;
    cin >> n >> m;

    graph g(2 * n);
    for (size_t i = 0; i < g.size(); i++) {
      g[i] = make_shared<node>();
      g[i]->pos = i / 2;
      g[i]->type = 1 + i % 2;
    }

    for (ll i = 0; i < m; i++) {
      ll a, b; char trigger, type;
      cin >> a >> trigger >> b >> type;
      ll u = (a - 1) * 2 + (trigger == 'V' ? 0 : 1);
      ll v = (b - 1) * 2 + (type == 'V' ? 0 : 1);
      g[u]->adjusted.emplace_back(g[v]);
      u = (b - 1) * 2 + (type == 'V' ? 1 : 0);
      v = (a - 1) * 2 + (trigger == 'V' ? 1 : 0);
      g[u]->adjusted.emplace_back(g[v]);
    }
    vi possible(n, y);
    vi values(n);
    string s;
    cin >> s;
    for (ll i = 0; i < n; i++) values[i] = s[i] - 'a';
    // for (ll i = 0; i < n; i++) cerr << possible[i];
    // cerr << endl;
    for (size_t i = 0; i < g.size(); i++) {
      if ((possible[g[i]->pos] & g[i]->type) == 0) continue;
      // cerr << possible[g[i]->pos] << " " << g[i]->type << endl;
      g[i]->possible = get_possible(possible, g[i], g);
      if (!valid(g[i]->possible)) possible[g[i]->pos] -= g[i]->type;
    }
    // for (ll i = 0; i < n; i++) cerr << possible[i];
    // cerr << endl;
    // break;
    if (solve(0, types, possible, values, g)) {
      for (ll i = 0; i < n; i++) {
        cout << (char)(values[i] + 'a');
      }
      cout << endl;
    } else {
      cout << -1 << endl;
    }
  }
}
