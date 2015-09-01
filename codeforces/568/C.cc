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
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct node {
  ll id;
  ll t;
  int type; // 0 - unknown, 1 - vowel, 2 - consolant
  vector<pedge> adjusted;
};

struct edge {
  pnode from, to;
  int trigger, type;
};

void connect(pnode &a, pnode &b, int trigger, int type) {
  pedge ea = make_shared<edge>();
  pedge eb = make_shared<edge>();
  ea->from = a; ea->to = b; ea->trigger = trigger; ea->type = type;
  eb->from = b; eb->to = a; eb->trigger = 3 - type; eb->type = 3 - trigger;
  a->adjusted.emplace_back(ea);
  b->adjusted.emplace_back(eb);
}

char find_letter(vi& az, char from, int type) {
  for (ll i = from - 'a'; i < (ll)az.size(); i++) {
    if (az[i] == type) return 'a' + i;
  }
  return '!';
}

ll T = 0;

bool dfs(pnode u, int type, string& s, vi& az) {
  assert(u->type == 0);
  u->type = type;
  u->t = T;
  T++;
  if (find_letter(az, s[u->id], type) == '!') return false;
  for (auto e : u->adjusted) {
    if (e->trigger != type) continue;
    auto v = e->to;
    if (v->type == 0) {
      if (!dfs(v, e->type, s, az)) return false;
    } else {
      if (v->type != e->type) return false;
    }
  }
  return true;
}

void revert(graph& g, ll t) {
  for (auto u : g) if (u->t >= t) u->type = 0;
}

bool try_set(string& s, ll pos, vi& az, graph& g) {
  if (pos == (ll)s.size()) return true;
  if (g[pos]->type) {
    s[pos] = find_letter(az, s[pos], g[pos]->type);
    if (s[pos] == '!') return false;
    return try_set(s, pos + 1, az, g);
  }
  int k = s[pos] - 'a';
  auto t = az[k];
  ll back = T;
  if (dfs(g[pos], t, s, az) && try_set(s, pos + 1, az, g)) return true;
  revert(g, back);
  k++;
  if (k >= (ll)az.size()) return false;
  s[pos] = k + 'a';
  t = az[k];
  for (ll i = pos + 1; i < s.size(); i++) s[i] = 'a';
  back = T;
  if (dfs(g[pos], t, s, az) && try_set(s, pos + 1, az, g)) return true;
  revert(g, back);
  t = 3 - t;
  s[pos] = find_letter(az, s[pos], t);
  if (s[pos] == '!') return false;
  for (ll i = pos + 1; i < (ll)s.size(); i++) s[i] = 'a';
  if (dfs(g[pos], t, s, az) && try_set(s, pos + 1, az, g)) return true;
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  string VC;
  while (cin >> VC) {
    vi az(VC.size());
    for (ll i = 0; i < az.size(); i++) az[i] = (VC[i] == 'V' ? 1 : 2);
    ll n, m;
    cin >> n >> m;
    graph g(n);
    for (ll i = 0; i < n; i++) {
      g[i] = make_shared<node>();
      g[i]->type = 0;
      g[i]->id = i;
    }
    for (ll i = 0; i < m; i++) {
      ll a, b; char trigger, type;
      cin >> a >> trigger >> b >> type;
      a--; b--;
      trigger = (trigger == 'V' ? 1 : 2);
      type = (type == 'V' ? 1 : 2);
      connect(g[a], g[b], trigger, type);
    }
    string s;
    cin >> s;
    if (!try_set(s, 0, az, g)) {
      cout << -1 << endl;
    } else {
      cout << s << endl;
    }
  }
}
