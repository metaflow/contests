#if defined(LOCAL)
#define PROBLEM_NAME "b"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
#define I(x, ...) (x)
#define C(x...) CHECK(x)
#else
#define L(x, ...) (x)
#define I(x, ...) (x)
#define C(x, ...) ;
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>; using vvvi = vector<vvi>;
using ii = pair<int,int>; using lu = unsigned long long; using l = long long;
using vs = vector<string>; using vii = vector<ii>;
using vl = vector<l>; using vvl = vector<vl>; using vvvl = vector<vvl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<l>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

const l MOD = e9 + 7;

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

void walk_preorder(l i, l& t, auto const& left, auto const& right, auto& preorder) {
  if (i < 0) return;
  preorder[t++] = i;
  walk_preorder(left[i], t, left, right, preorder);
  walk_preorder(right[i], t, left, right, preorder);
}

void walk_postorder(l i, l& t, auto const& left, auto const& right,
                    auto const& preorder, auto& s) {
  if (i < 0) return;
  walk_postorder(left[i], t, left, right, preorder, s);
  walk_postorder(right[i], t, left, right, preorder, s);
  s.connect(i, preorder[t++]);
}

void solve(istream& cin, ostream& cout) {
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    l n, k; cin >> n >> k;
    vl left(n, -1), right(n, -1);
    F(i, 0, n) {
      cin >> left[i] >> right[i];
      left[i]--; right[i]--;
    }
    vl preorder(n);
    l t = 0;
    walk_preorder(0, t, left, right, preorder);
    L(preorder);
    disjoint_set s(n);
    t = 0;
    walk_postorder(0, t, left, right, preorder, s);
    cout << "Case #" << tc << ": ";
    if (I(s.components_count()) < I(k)) {
      cout << "Impossible" << lf;
    } else {
      vl color(n);
      l j = 0;
      F(i, 0, n) {
        l p = s.get_parent(i);
        if (color[p] == 0) color[p] = j + 1, j = (j + 1) % k;
        if (i) cout << ' ';
        cout << color[p];
      }
      cout << lf;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
