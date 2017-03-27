#include <bits/stdc++.h>

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
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
#define ALL(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

l gcd(l a, l b) {
  while (b) { l t = b; b = a % b; a = t; }
  return a;
}

l lcm(l a, l b) { return a * b / gcd(a, b); }

l dfs(l u, l parent, vvl& adj, vl& v, vl& d) {
  if (v[u]) return 0;
  l r = 0;
  l m = numeric_limits<l>::max();
  l sum = 0;
  for (l i : adj[u]) {
    if (i == parent) continue;
    r += dfs(i, u, adj, v, d);
    m = min(m, v[i]);
    d[u] = (d[u] and d[i]) ? lcm(d[u], d[i]) : 0;
    sum += v[i];
  }
  l c = adj[u].size();
  if (parent != -1) c--;
  v[u] = d[u] ? (m / d[u]) * d[u] * c : 0;
  r += sum - v[u];
  d[u] *= c;
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vl v(n);
    F(i, 0, n) cin >> v[i];
    vvl adj(n);
    F(i, 0, n - 1) {
      l a, b; cin >> a >> b; a--; b--;
      adj[a].emplace_back(b);
      adj[b].emplace_back(a);
    }
    vl d(n, 1);
    cout << dfs(0, -1, adj, v, d) << '\n';
  }
}
