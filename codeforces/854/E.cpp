#if defined(LOCAL)
#define PROBLEM_NAME "E"
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

// [1, n]
struct BIT {
  vl tree;
  l max_p;
  BIT(size_t n) {
    max_p = n;
    tree.resize(n + 1);
  };
  // sum of [1, p], O(log(max))
  l get(l p) {
    l sum = 0;
    while (p) {
      sum += tree[p];
      p -= (p & -p);
    }
    return sum;
  }
  l get(l from, l to) { // [from, to]
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

struct Query {
  l x0, y0, x1, y1, answer, id;
};

void solve(istream& cin, ostream& cout) {
  l n, q; cin >> n >> q;
  vl y(n + 1);
  F(i, 0, n) cin >> y[i + 1];
  vector<Query> qq(q);
  F(i, 0, q) cin >> qq[i].x0 >> qq[i].y0
                 >> qq[i].x1 >> qq[i].y1;
  F(i, 0, q) {
    qq[i].id = i;
    qq[i].answer = n * (n - 1);
    l t = qq[i].x0 - 1;
    qq[i].answer -= t * (t - 1);
    t = n - qq[i].x1;
    qq[i].answer -= t * (t - 1);
    t = qq[i].y0 - 1;
    qq[i].answer -= t * (t - 1);
    t = n - qq[i].y1;
    qq[i].answer -= t * (t - 1);
  }
  // left -> right
  {
    sort(all(qq), [](const Query& a, const Query& b) {
        return a.x0 < b.x0;
      });
    BIT bit(n);
    l p = 0;
    F(i, 0, q) {
      while (p + 1 < qq[i].x0) {
        p++;
        bit.add(y[p], 1);
      }
      l t = bit.get(qq[i].y0 - 1);
      qq[i].answer += t * (t - 1);
      t = qq[i].x0 - 1 - bit.get(qq[i].y1);
      qq[i].answer += t * (t - 1);
    }
  }
  // right->left
  {
    sort(all(qq), [](const Query& a, const Query& b) {
        return a.x1 > b.x1;
      });
    BIT bit(n);
    l p = n + 1;
    F(i, 0, q) {
      while (p - 1 > qq[i].x1) {
        p--;
        bit.add(y[p], 1);
      }
      l t = bit.get(qq[i].y0 - 1);
      qq[i].answer += t * (t - 1);
      t = n - qq[i].x1 - bit.get(qq[i].y1);
      qq[i].answer += t * (t - 1);
    }
  }
  sort(all(qq), [](const Query& a, Query const& b) {
      return a.id < b.id;
    });
  for (auto a : qq) cout << a.answer / 2 << lf;
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
