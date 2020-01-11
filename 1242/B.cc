#if defined(LOCAL)
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#endif
#include <math.h>
#include <algorithm>
#include <bitset>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using ii = pair<int, int>;
using lu = unsigned long long;
using l = long long;
using vs = vector<string>;
using vii = vector<ii>;
using vl = vector<l>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vlu = vector<lu>;
using ll = pair<l, l>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vvvb = vector<vvb>;
using vd = vector<double>;
using vvd = vector<vd>;
using mll = unordered_map<l, l>;
using sl = unordered_set<l>;
const l      INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const double PI = 3.14159265358979323846;
const l      e0 = 1, e3 = 1000, e5 = 100000, e6 = 10 * e5, e7 = 10 * e6,
  e8 = 10 * e7, e9 = 10 * e8, l0 = 0, l1 = 1, l2 = 2;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a, b, c) for (l a = l(b); a < l(c); a++)
#define B(a, b, c) for (l a = l(c) - 1; a >= l(b); a--)

void solve(istream &in, ostream &out);
void solve_brute(istream &, ostream &);
bool interactive_judge(istream &, istream &, ostream &);
bool generate_random(l, ostream &);
bool solution_checker(istream &, istream &, istream &, ostream &);
int  main(int argc, char **argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  tst::test_init(argc, argv);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _judge = interactive_judge;
  // _custom_solution_checker = solution_checker;
  tst::maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
const l MOD = e9 + 7;  // end of template

// intervals are inclusive [a, b]
// e.g. [1, 2] + [2, 3] -> [1, 3]
// [1, 4] - [2, 3] -> [1, 1], [4, 4]
// and find([4, 7]) -> ([1, 4], [5, 6], [7, 11])
class MergedIntervals {
private:
  struct cmp {
    bool operator() (const ll& a, const ll& b) const { // TODO: update template
      return a.second < b.first;
    };
  };
  set<ll, cmp> m;
  friend ostream& operator << (ostream& s, const MergedIntervals& v) {
    for (auto i = v.m.cbegin(); i != v.m.cend(); i++) {
      s << "[" << i->first << ", " << i->second << "] ";
    }
    return s;
  }
public:
  void add(l a, l b) {
    auto p = m.equal_range(make_pair(a, b));
    for (auto i = p.first; i != p.second; i++) {
      a = min(a, i->first);
      b = max(b, i->second);
    }
    m.erase(p.first, p.second);
    m.emplace(make_pair(a, b));
  }

  void remove(l a, l b) {
    auto p = m.equal_range(make_pair(a, b));
    vll r;
    for (auto i = p.first; i != p.second; i++) r.emplace_back(*i);
    m.erase(p.first, p.second);
    for (auto i : r) {
      if (i.first < a) {
        m.emplace(make_pair(i.first, min(a, i.second) - 1));
      }
      if (i.second > b) {
        m.emplace(make_pair(max(b, i.first) + 1, i.second));
      }
    }
  }

  // returns all intervals intersecting with [a,b]
  // may be outside of [a, b]
  vll find(l a, l b) {
    vll r;
    auto p = m.equal_range(make_pair(a, b));
    for (auto i = p.first; i != p.second; i++) r.emplace_back(*i);
    return r;
  }

  bool intersectsWith(l a, l b) {
    auto p = m.equal_range(make_pair(a, b));
    return p.first != p.second;
  }

  // all intervals ordered
  vll intervals() {
    vll r;
    r.insert(r.begin(), m.cbegin(), m.cend());
    return r;
  }
};

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


void solve(istream &in, ostream &out) {
  l n, m;
  in >> n >> m;
  unordered_map<l, set<l>> e;
  F(i, 0, m) {
    l a, b; in >> a >> b;
    e[a].emplace(b);
    e[b].emplace(a);
  }
  MergedIntervals ii;
  F(i, 1, n + 1) {
    l p = 0;
    for (auto x : e[i]) {
      l from = p + 1;
      l to = x - 1;
      if (from < to) ii.add(from, to);
      p = x;
    }
    l from = p + 1;
    l to = n;
    if (from < to) ii.add(from, to);
  }
  disjoint_set ds(n);
  for (auto ab : ii.intervals()) {
    auto [a, b] = ab;
    F(i, a, b) {
      ds.connect(i - 1, b - 1);
    }
  }
  F(i, 1, n + 1) {
    l p = 0;
    for (auto x : e[i]) {
      l from = p + 1;
      l to = x - 1;
      if (from <= to) {
        ds.connect(i - 1, to - 1);
      }
      p = x;
    }
    l from = p + 1;
    l to = n;
    if (from <= to) ds.connect(i - 1, to - 1);
  }
  out << ds.components_count() - 1 << lf;
}
