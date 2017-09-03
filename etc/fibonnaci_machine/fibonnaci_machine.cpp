#if defined(LOCAL)
#define TIME 2
#define PROBLEM_NAME "fibonnaci_machine"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) debug(x)
#else
#define L(x...) (x)
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

const l MOD = e9 + 7;

vl mult22(vl& a, vl& b) {
  vl r(4);
  F(i, 0, 2) F(j, 0, 2) F(k, 0, 2)
    r[i * 2 + j] = (r[2 * i + j] + a[2 * i + k] * b[2 * k + j]) % MOD;
 return r;
}

vl mult21(vl& a, vl& b) {
  vl r(2);
  F(i, 0, 2) F(k, 0, 2) r[i] = (r[i] + a[2 * i + k] * b[k]) % MOD;
  return r;
}

vvl mpows;

// [0, size), get / add intervals are inlclusive // TODO: update snippet
class SegmentTree {
  l n;
  vl low, high, delta;
  vvl v;

  void init(l i, l a, l b) {
    low[i] = a;
    high[i] = b;
    v[i][0] = 0;
    v[i][1] = 1;
    if (a == b) return;
    l m = a + (b - a) / 2;
    init(2 * i, a, m);
    init(2 * i + 1, m + 1, b);
    update(i); // TODO: update snippet
  }

  void propagate(l p) {
    delta[2 * p] += delta[p];
    delta[2 * p + 1] += delta[p];
    delta[p] = 0;
  }

  vl merge(vl a, vl b) {
    vl r = {(a[0] + b[0]) % MOD, (a[1] + b[1]) % MOD};
    return r;
  }

  vl get(l p, l a, l b) {
    if (b < low[p] or high[p] < a) return {0, 0};
    if (a <= low[p] and high[p] <= b) {
      // TODO: mark this
      return mult21(mpows[delta[p]], v[p]);
    }
    propagate(p);
    auto r = merge(get(p * 2, a, b),
                   get(p * 2 + 1, a, b));
    update(p);
    return r;
  }

  void update(l p) {
    v[p] = merge(get(p * 2, low[p], high[p]),
                 get(p * 2 + 1, low[p], high[p]));
  }

  void add(l p, l a, l b, l value) {
    if (b < low[p] or high[p] < a) return;

    if (a <= low[p] and high[p] <= b) {
      delta[p] += value;
      return;
    }

    propagate(p);
    add(2 * p, a, b, value);
    add(2 * p + 1, a, b, value);
    update(p);
  }

public:
  SegmentTree(l size) {
    n = 1;
    while (n < size) n = n << 1;
    n = n << 1;
    v.resize(n, vl(2));
    low.resize(n);
    high.resize(n);
    delta.resize(n);
    init(1, 0, size - 1);
  }

  void add(l a, l b, l value) {
    add(1, a, b, value);
  }

  l get(l a, l b) {
    return get(1, a, b)[0];
  }
};


void solve(istream& cin, ostream& cout) {
  l n, k;
  cin >> n >> k;
  mpows.resize(k + 1);
  mpows[0] = {1, 0,
              0, 1};
  mpows[1] = {0, 1,
              1, 1};
  F(i, 2, k + 1) mpows[i] = mult22(mpows[i - 1], mpows[1]);
  SegmentTree st(n);
  F(i, 0, k) {
    char op; l a, b; cin >> op >> a >> b; a--; b--;
    if (op == 'D') {
      st.add(a, b, 1);
    } else {
      cout << st.get(a, b) << lf;
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
