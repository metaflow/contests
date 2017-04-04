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

struct disjoint_set { // set of [0..n-1]
  vl parent;
  l components_count_;

  disjoint_set(size_t n) {
    components_count_ = n;
    parent.resize(n);
    for (size_t i = 0; i < n; i++) parent[i] = i;
  }
  l get_parent(l i) {
    if (parent[i] != i) parent[i] = get_parent(parent[i]);
    return parent[i];
  }
  bool connected(l i, l j) { return get_parent(i) == get_parent(j); }
  void connect(l i, l j) {
    i = get_parent(i);
    j = get_parent(j);
    if (i != j) {
      parent[i] = j;
      components_count_--;
    }
  }
  l components_count() { return components_count_; }
};

const l dx[4] = {0, 0, -1, 1};
const l dy[4] = {-1, 1, 0, 0};

bool good(l i, l j, l n, l m) {
  return (i >= 0) and (i < n) and (j >= 0) and (j < m);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> n >> m) {
    vvl v(n, vl(m));
    F(i, 0, n) F(j, 0, m) cin >> v[i][j];
    disjoint_set s(n * m);
    F(i, 0, n) F(j, 0, m) {
      if (v[i][j] == 0) continue;
      F(d, 0, 4) {
        l x = i + dx[d];
        l y = j + dy[d];
        if (good(x, y, n, m) and v[x][y]) s.connect(i * m + j, x * m + y);
      }
    }
    vl sizes(n * m);
    F(i, 0, n) F(j, 0, m) {
      if (v[i][j]) sizes[s.get_parent(i * m + j)]++;
    }
    l best = 1;
    F(i, 0, n) F(j, 0, m) {
      if (v[i][j]) continue;
      unordered_set<l> u;
      F(d, 0, 4) {
        l x = i + dx[d], y = j + dy[d];
        if (good(x, y, n, m) and v[x][y]) u.emplace(s.get_parent(x * m + y));
      }
      l t = 1;
      for (auto k : u) t += sizes[k];
      best = max(best, t);
    }
    cout << best << '\n';
  }
}
