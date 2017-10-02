#if defined(LOCAL)
#define PROBLEM_NAME "f"
const double _max_double_error = 1e-9;
#include "testutils.h"
#define L(x...) (debug(x, #x))
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
#define max(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x>__y?__x:__y;})
#define min(a,b)({__typeof__(a)__x=(a);__typeof__(b)__y=(b);__x<__y?__x:__y;})

unordered_set<l> bad;

const l MOD = e9 + 7;
l h(l x, vl& v) {
  l z = x;
  for (auto i : v) z = (z * 100 + i) % MOD;
  return z;
}

bool f(l d, l top, vl& v, vvl& s, vl& target) {
  l key = h(top - d, v);
  if (bad.count(key)) return false;
  l n = v.size();
  s.resize(d + 1);
  s[d] = v;
  l p = 0;
  auto q = target;
  for (auto i : v) {
    assert(p < q.size());
    if (i > q[p]) {
      bad.emplace(key);
      return false;
    }
    q[p] -= i;
    if (q[p] == 0) p++;
  }
  if (d == top) {
    bool ok = v == target;
    if (not ok) bad.emplace(key);
    return ok;
  }
  F(i, 0, n) {
    for (l j = i + 2; j <= n; j += 2) {
      vl c;
      F(k, 0, i) c.emplace_back(v[k]);
      for (l k = i; k < j; k += 2) c.emplace_back(v[k] + v[k + 1]);
      F(k, j, n) c.emplace_back(v[k]);
      // L(c);
      if (f(d + 1, top, c, s, target)) return true;
    }
  }
  bad.emplace(key);
  return false;
}

void show(vl v, vl t) {
  l p = 0;
  cout << " ";
  for (auto i : v) {
    cout << i;
    t[p] -= i;
    if (t[p]) {
      cout << " ";
    } else {
      cout << " | ";
      p++;
    }
  }
  cout << "" << endl;
}

pair<l, vvl> ss(vl& target, l m) {
  bad.clear();
  l k = accumulate(all(target), l(0));
  vl v(k, 1);
  l steps = 0;
  while (steps <= m) {
    vvl s;
    if (f(0, steps, v, s, target)) {
      return make_pair(steps, s);
    }
    steps++;
  }
  return make_pair(-1, vvl(0));
}

void solve(istream& cin, ostream& cout) {
  //
  // F(i, 1, 16) {
    // vl v(1, i);
    // l m = ss(v, 10).first;
    // l j = 1;
    // while (1) {
      // vl q(3);
      // q[0] = 1 << m;
      // q[1] = i;
      // q[2] = 1 << j;
      // if (ss(q, m).first == -1) {
        // cout << i << ' ' <<  bitset<4>(i) << ' ' << m << " / " << j - 1 << endl;
        // break;
      // }
      // j++;
    // }
  // }
  l n; cin >> n;
  vl target(n);
  F(i, 0, n) cin >> target[i];
  vl u(n), d(n);
  l answer = 0;
  F(i, 0, n) {
    l k = 0; while ((1 << (1 + k)) <= target[i]) k++;
    u[i] = d[i] = k;
    if (target[i] > (1 << k)) u[i]++;
    answer += u[i];
  }
  bool prev = true; // prev facing [d, u]
  F(i, 1, n) {
    l x = prev ? u[i - 1] : d[i - 1];
    if (x <= d[i]) {
      prev = true;
      answer -= min(x, d[i]);
    } else {
      prev = false;
      answer -= min(x, u[i]);
    }
  }
  cout << answer << lf;
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
