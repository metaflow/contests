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
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <functional> // TODO: template
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
using vd = vector<double>;
using vvd = vector<vd>;
using mll = unordered_map<l, l>;
using sl = unordered_set<l>;
const l      INF = numeric_limits<l>::max();
const double EPS = 1e-10;
const double PI = 3.14159265358979323846;
const l      e0 = 1, e3 = 1000, e5 = 100000, e6 = 10 * e5, e7 = 10 * e6,
        e8 = 10 * e7, e9 = 10 * e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a, b, c) for (l a = l(b); a < l(c); a++)
#define B(a, b, c) for (l a = l(c) - 1; a >= l(b); a--)
#define VVL(x, a, b, i) vvl x(a, vl(b, l(i)));
#define VVVL(x, a, b, c, i) vvvl x(a, vvl(b, vl(c, l(i))));

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
using l4 = tuple<l, l>;

// finds lowest x: f(x) = true, x within [a, b), b if f(b - 1) = false
l binary_search_lower(l a, l b, function<bool(l)> f) {
  l count = b - a;
  while (count > 0) {
    l step = count / 2;
    l m = a + step;
    if (f(m)) {
      count = step;
    } else {
      a = m + 1;
      count -= step + 1;
    }
  }
  return a;
}

// finds lowest x: f(x) = true, x within [a, b)
double binary_search_lower_double(double a, double b,
                                  function<bool(double)> f) {
  double diff = b - a;
  while (diff > EPS) {
    diff /= 2;
    double m = a + diff;
    if (!f(m)) a = m;
  }
  return a;
}

void solve(istream &in, ostream &out) {
  l n;
  in >> n;
  vector<l4> a(n), b(n);
  map<ll, vl> aph, bph;
  F(i, 0, n) in >> get<0>(a[i]);
  F(i, 0, n) in >> get<1>(a[i]);
  F(i, 0, n) aph[ll(get<0>(a[i]), get<1>(a[i]))].emplace_back(i + 1);
  F(i, 0, n) in >> get<0>(b[i]);
  F(i, 0, n) in >> get<1>(b[i]);
  F(i, 0, n) bph[ll(get<0>(b[i]), get<1>(b[i]))].emplace_back(i + 1);
  auto a_index = [&] (const l p, const l h) -> l {
                   ll idx(p, h);
                   auto& r = aph[idx];
                   if (r.empty()) return 0;
                   l z = r.back();
                   r.pop_back();
                   return z;
                 };
  auto b_index = [&] (const l p, const l h) -> l{
                   ll idx(p, h);
                   auto& r = bph[idx];
                   if (r.empty()) return 0;
                   l z = r.back();
                   r.pop_back();
                   return z;
                 };
  sort(all(a));
  sort(all(b));
  L(0);
  L(a);
  L(b);
  l pa = 0; l pb = 0;
  l price_a, price_b;
  multiset<l> sa, sb;
  vl za, zb; za.reserve(n); zb.reserve(n);
  bool ok = true;
  while ((pa < n or pb < n) and ok) {
    if (sa.empty()) {
      price_a = get<0>(a[pa]);
      while (pa < n and get<0>(a[pa]) == price_a) {
        sa.emplace(get<1>(a[pa]));
        pa++;
      }
    }
    if (sb.empty()) {
      price_b = get<0>(b[pb]);
      while (pb < n and get<0>(b[pb]) == price_b) {
        sb.emplace(get<1>(b[pb]));
        pb++;
      }
    }
    if (sa.empty() or sb.empty()) return;
    L(sa, sb);
    if (sa.size() <= sb.size()) {
      auto x = sa.begin();
      while (x != sa.end()) {
        auto y = sb.lower_bound(*x);
        if (y == sb.begin()) {
          ok = false;
          break;
        }
        y = prev(y);
        za.emplace_back(a_index(price_a, *x));
        zb.emplace_back(b_index(price_b, *y));
        sb.erase(y);
        x++;
      }
      sa.clear();
    } else {
      auto y = sb.begin();
      while (y != sb.end()) {
        auto x = sa.upper_bound(*y);
        if (x == sa.end()) {
          ok = false;
          break;
        }
        za.emplace_back(a_index(price_a, *x));
        zb.emplace_back(b_index(price_b, *y));
        sa.erase(x);
        y++;
      }
      sb.clear();
    }
  }
  if (not ok) {
    out << "impossible" << lf;
    return;
  }
  F(i, 0, za.size()) {if (i != 0) out << ' '; out << za[i];} out << lf;
  F(i, 0, zb.size()) {if (i != 0) out << ' '; out << zb[i];} out << lf;
}
