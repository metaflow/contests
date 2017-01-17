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

struct disjoint_set {
  vl parent;
  disjoint_set(size_t n) {
    parent.resize(n);
    for (size_t i = 0; i < n; i++) {
      parent[i] = i;
    }
  }
  l get_parent(l i) {
    if (parent[i] != i) parent[i] = get_parent(parent[i]);
    return parent[i];
  }
  bool connected(l i, l j) {
    return get_parent(i) == get_parent(j);
  }
  void connect(l i, l j) {
    l a = get_parent(i);
    l b = get_parent(j);
    parent[a] = b;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    disjoint_set s(n);
    for (l i = 0; i < n; i++) {
      l a; cin >> a; a--;
      s.connect(i, a);
    }
    unordered_set<l> u;
    for (l i = 0; i < n; i++) {
      u.emplace(s.get_parent(i));
    }
    cout << u.size() << endl;
  }
}
