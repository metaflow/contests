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
// [1, n]
struct BIT {
  vl tree;
  l max_p;
  BIT(size_t n) {
    max_p = n;
    tree.resize(n + 1);
  };
  l get(l p) {  // sum of [1, p], O(log(max))
    l sum = 0;
    while (p) {
      sum += tree[p];
      p -= (p & -p);
    }
    return sum;
  }
  l get(l from, l to) {  // [from, to]
    return get(to) - get(from - 1);
  }
  // O(log(max))
  void add(l p, l value) {
    while (p <= max_p) {
      tree[p] += value;
      p += (p & -p);
    }
  }
  // find lowest index with given sum, -1 if not found O(log(max))
  l find(l sum) {
    l mask = max_p;
    while (true) {
      l lower = (mask & -mask);
      if (lower == mask) break;
      mask -= lower;
    }
    l p = 0;
    l top = -1;
    while (mask != 0) {
      l m = p + mask;
      if (m <= max_p) {
        if (sum == tree[m]) top = m;
        if (sum > tree[m]) {
          p = m;
          sum -= tree[m];
        }
      }
      mask >>= 1;
    }
    if (sum != 0) return top;
    return p;
  }
};


void solve(istream &in, ostream &out) {
  l n;
  in >> n;
  vl v(n);
  F(i, 0, n) in >> v[i];
  vll s(n);
  F(i, 0, n) s[i] = {-v[i], i};
  sort(all(s));
  L(s);
  l m; in >> m;
  vector<tuple<l, l, l>> q(m);
  F(i, 0, m) {
    l a, b; in >> a >> b;
    q[i] = {a, b, i};
  }
  sort(all(q));
  l kk = 0;
  BIT bit(n);
  vl z(m);
  for (auto j : q) {
    l k = get<0>(j);
    while (kk < k) {
      bit.add(s[kk].second + 1, 1);
      kk++;
    }
    l p = get<1>(j);
    l i = bit.find(p);
    L(k, p, i, v[i - 1]);
    z[get<2>(j)] = v[i - 1];
  }
  F(i, 0, m) out << z[i] << lf;
}
