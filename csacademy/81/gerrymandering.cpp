#if defined(LOCAL)
#define PROBLEM_NAME "gerrymandering"
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

vvl rmq_preprocess(vl& A) {
  l n = A.size();
  vvl R(1, vl(n));
  for (l i = 0; i < n; i++) R[0][i] = i;
  for (l k = 1; 2 * k <= n; k = k << 1) {
    vl V;
    for (l i = 0; i + 2 * k <= n; i++) {
      if (A[R.back()[i]] < A[R.back()[i + k]]) {
        V.emplace_back(R.back()[i]);
      } else {
        V.emplace_back(R.back()[i + k]);
      }
    }
    R.emplace_back(V);
  }
  return R;
}

// range minimum query [from, to)
l rmq(l from, l to, vl& A, vvl& P) {
  l q = P.size() - 1;
  l k = (l)1 << q;
  while (k > (to - from)) { k = k >> 1; q--; }
  l i = P[q][from];
  l j = P[q][to - k];
  return (A[i] < A[j]) ? i : j;
}

l dfs(l p, auto& large, auto& acc, auto& acc_pos, auto& r, auto& state) {
  auto& z = state[p];
  if (z > -1) return z;
  z = 0;
  auto a = lower_bound(all(large), p);
  C(a != large.end());
  auto b = a + 1;
  // last one
  if (b == large.end()) {
    I(p, "last");
    return z = acc.back() - acc[p] >= 0;
  }
  // B domination
  auto j = rmq(*a + 1, *b + 1, acc, r);
  I(p, j);
  if (acc[j] - acc[p] < 0) z = dfs(j, large, acc, acc_pos, r, state);
  // A domination
  // exactly 0 sum
  auto& pos = acc_pos[acc[p]];
  auto i = lower_bound(all(pos), p + 1);
  if (i == pos.end() or *i > *b) {
    // same sign everywhere in this segment
    if (acc[j] - acc[p] >= 0) {
      z = max(z, 1 + dfs(j, large, acc, acc_pos, r, state));
    }
  } else {
    z = max(z, 1 + dfs(*i, large, acc, acc_pos, r, state));
  }
  return z;
}

void solve(istream& cin, ostream& cout) {
  l n; cin >> n;
  vl v(n);
  vl large;
  F(i, 0, n) {
    char a, b; cin >> a >> b;
    v[i] = a == 'A' ? 1 : -1;
    if (b == 'L') large.emplace_back(i);
  }
  I(large);
  vl acc(n + 1);
  F(i, 0, n) acc[i + 1] = acc[i] + v[i];
  unordered_map<l, vl> acc_pos;
  F(i, 0, n + 1) acc_pos[acc[i]].emplace_back(i);
  auto r = rmq_preprocess(acc);
  vl state(n, -1);
  cout << dfs(0, large, acc, acc_pos, r, state) << lf;
}

l dfs_brute(l p, l left, auto& state, auto& v, auto& large) {
  const l n = state.size();
  l &z = state[p];
  if (z != -1) return z;
  l sum = 0;
  if (left == 1) {
    F(i, p, state.size()) sum += v[i];
    z = sum >= 0;
    return z;
  }
  l i = p;
  while (i < n and not large[i]) {
    sum += v[i];
    ++i;
  }
  do {
    sum += v[i];
    z = max(z, (sum >= 0) + dfs_brute(i + 1, left - 1, state, v, large));
    ++i;
  } while (not large[i]);
  return z;
}

void solve_brute(istream& cin, ostream& cout) {
  l n; cin >> n;
  vl v(n);
  l large_count = 0;
  vb large(n);
  F(i, 0, n) {
    char c, s; cin >> c >> s;
    v[i] = 1 - 2 * (c == 'B');
    large[i] = s == 'L';
    large_count += s == 'L';
  }
  vl state(n, -1);
  cout << dfs_brute(0, large_count, state, v, large) << lf;
}

// return false to stop
bool generate_random(l tc, ostream& cout) {
  l max_cases = 10000;
  if (tc % (max_cases / 100) == 0) cerr << (tc * 100 / max_cases) << "%\r";

  return tc < max_cases;
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
  // solve(cin, cout);
  solve_brute(cin, cout);
#endif
}
