#if defined(LOCAL)
#define PROBLEM_NAME "C"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#include <bits/stdc++.h>
#endif

using namespace std;
using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
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

#if defined(LOCAL)
#define L(x...) debug(x)
#else
#define L(x, ...) (x)
#endif

// finds lowest x: f(x) = true, x within [a, b), b if f(b - 1) = false
// TODO: binary_search_lower double
double binary_search_lower(double a, double b, function<bool(double)> f) {
  double diff = b - a;
  while (diff > EPS) {
    diff /= 2;
    double m = a + diff;
    if (!f(m)) a = m;
  }
  return a;
}

// intervals are inclusive [a, b]
// e.g. [1, 2] + [2, 3] -> [1, 3]
// [1, 4] - [2, 3] -> [1, 1], [4, 4]
// and find([4, 7]) -> ([1, 4], [5, 6], [7, 11])
class MergedIntervals {
private:
  struct cmp {
    bool operator() (const ll& a, const ll& b) {
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

struct man { l x; double v, t_v, t_vs; };

void solve(istream& cin, ostream& cout) {
  l N, S;
  while (cin >> N >> S) {
    vector<man> to_left, to_right;
    double min_t_left = e6, min_t_right = e6;
    double max_t_left = e6, max_t_right = e6;
    F(i, 0, N) {
      man m; l d;
      cin >> m.x >> m.v >> d;
      if (d == 1) {
        m.t_v = m.x / m.v;
        max_t_left = min(max_t_left, m.t_v);
        m.t_vs = m.x / (m.v + S);
        min_t_left = min(min_t_left, m.t_vs);
        to_left.emplace_back(m);
      } else {
        m.t_v = (e6 - m.x) / m.v;
        max_t_right = min(max_t_right, m.t_v);
        m.t_vs = (e6 - m.x) / (m.v + S);
        min_t_right = min(min_t_right, m.t_vs);
        to_right.emplace_back(m);
      }
    }
    double min_t = max(min_t_left, min_t_right);
    double max_t = min(max(max_t_left, min_t_right), max(max_t_right, min_t_left));
    L("t", min_t, "..", max_t);
    sort(all(to_left), [](const man& a, const man& b) {return a.t_vs < b.t_vs;});
    sort(all(to_right), [](const man& a, const man& b) {return a.t_vs < b.t_vs;});
    double answer = binary_search_lower(min_t, max_t, [&](double t) {
        auto left_end = upper_bound(all(to_left), t,
                                    [](double x, const man& m) {return x < m.t_vs;});
        auto right_end = upper_bound(all(to_right), t,
                                     [](double x, const man& m) {return x < m.t_vs;});
        MergedIntervals intervals;
        for (auto a = to_left.begin(); a != left_end; a++) {
          double x = a->x;
          double z = (x * (a->v + S) - t * a->v * (a->v + S)) / S;
          double r = (x * S - z * (S - a->v)) / a->v;
          // cerr << setprecision(15) << r << ' ' << l(r + EPS) << lf;
          intervals.add(a->x, l(r + EPS));
        }
        for (auto a = to_right.begin(); a != right_end; a++) {
          // TODO: output L only if test case failed
          double x = e6 - a->x;
          double z = (x * (a->v + S) - t * a->v * (a->v + S)) / S;
          double r = (x * S - z * (S - a->v)) / a->v;
          r = e6 - r;
          // TODO: precision in L()
          // cerr << setprecision(15) << r << lf;
          if (intervals.intersectsWith(ceil(r), a->x)) return true;
        }
        return false;
      });
    cout << fixed << setprecision(15) <<  answer << lf;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
  cerr << fixed << setprecision(15); // TODO: update template
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
  // _generate_random_test = generate_random;
  // _solve_brute = solve_brute;
  // _player_b = player_b;
  // _custom_solution_checker = solution_checker;
#else
  solve(cin, cout);
#endif
}
