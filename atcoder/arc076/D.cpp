#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "D"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

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


void solve(istream& cin, ostream& cout) {
  l n;
  while (cin >> n) {
    vll xx, yy;
    F(i, 0, n) {
      l x, y; cin >> x >> y;
      xx.emplace_back(x, i);
      yy.emplace_back(y, i);
    }
    sort(all(xx));
    sort(all(yy));
    vector<tuple<l, l, l>> dd;
    F(i, 1, n) {
      dd.emplace_back(xx[i].first - xx[i - 1].first, xx[i].second, xx[i - 1].second);
      dd.emplace_back(yy[i].first - yy[i - 1].first, yy[i].second, yy[i - 1].second);
    }
    sort(all(dd));
    disjoint_set s(n);
    l answer = 0;
    for (auto c : dd) {
      if (s.connected(get<1>(c), get<2>(c))) continue;
      s.connect(get<1>(c), get<2>(c));
      answer += get<0>(c);
    }
    cout << answer << lf;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
