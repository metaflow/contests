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
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

struct node;
struct edge;
using pnode = shared_ptr<node>;
using pedge = shared_ptr<edge>;
using graph = vector<pnode>;

struct disjoint_set { // set of [0..n-1]
  vl parent;
  vl neg;
  l components_count_;

  disjoint_set(size_t n) {
    components_count_ = n;
    parent.resize(n);
    neg.resize(n, - 1);
    for (size_t i = 0; i < n; i++) parent[i] = i;
  }
  l get_parent(l i) {
    if (parent[i] != i) parent[i] = get_parent(parent[i]);
    return parent[i];
  }
  bool same(l i, l j) { return get_parent(i) == get_parent(j); }
  bool connected(l i, l j) {
    i = get_parent(i);
    j = get_parent(j);
    return (i == j) or (neg[i] == j);
  }

  void syn(l i, l j) {
    i = get_parent(i);
    l ni = neg[i];
    j = get_parent(j);
    l nj = neg[j];
    parent[i] = j;
    if (ni > -1) {
      if (nj > -1) {
        parent[ni] = nj;
      } else {
        neg[j] = ni;
        neg[ni] = j;
      }
    }
  }

  void ant(l i, l j) {
    i = get_parent(i);
    l ni = neg[i];
    j = get_parent(j);
    l nj = neg[j];
    if (nj > -1) {
      parent[i] = nj;
    } else {
      neg[i] = j;
      neg[j] = i;
    }
    if (ni > -1) parent[ni] = j;
  }
  l components_count() { return components_count_; }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m, q;
  while (cin >> n >> m >> q) {
    map<string, l> w2l;
    for (l i = 0; i < n; i++) {
      string s; cin >> s;
      w2l[s] = i;
    }
    disjoint_set ds(n);
    for (l i = 0; i < m; i++) {
      bool ok = true;
      l t; string a, b;
      cin >> t >> a >> b;
      l x = w2l[a];
      l y = w2l[b];
      if (t == 1) {
        if (not ds.same(x, y)) {
          if (ds.connected(x, y)) {
            ok = false;
          } else {
            ds.syn(x, y);
          }
        }
      } else {
        if (ds.same(x, y)) {
          ok = false;
        } else {
          if (not ds.connected(x, y)) {
            ds.ant(x, y);
          }
        }
      }
      cout << (ok ? "YES\n" : "NO\n");
    }
    for (l i = 0; i < q; i++) {
      string a, b; cin >> a >> b;
      l x = w2l[a];
      l y = w2l[b];
      if (ds.connected(x, y)) {
        if (ds.same(x, y)) {
          cout << "1\n";
        } else {
          cout << "2\n";
        }
      } else {
        cout << "3\n";
      }
    }
  }
}
