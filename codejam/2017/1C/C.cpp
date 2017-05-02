#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

const l M = 10000;

double dfs(vvd& dp, vd& p, l at, l k) {
  if (at + 1 < k) return 0;
  if (k == 0) return 1;
  auto& r = dp[at][k];
  if (r < 0) {
    r = p[at] * dfs(dp, p, at - 1, k - 1) +
      (1 - p[at]) * dfs(dp, p, at - 1, k);
  }
  return r;
}

double prob(vd& p, l k) {
  l n = p.size();
  vvd dp(n, vd(k + 1, -1));
  return dfs(dp, p, n - 1, k);
}

struct Case {
  l n, k;
  double u;
  vd p;
  l id;
  double answer;
};

Case solve(Case c) {
  auto& p = c.p;
  auto& n = c.n;
  auto& k = c.k;
  auto& u = c.u;
  sort(all(p));
  double sum = p[0];
  l j = 1;
  while (j < n and ((sum + u) / j > p[j])) { sum += p[j]; j++; }
  F(i, 0, j) p[i] = (sum + u) / j;
  double v = prob(p, k);
  c.answer = v;
  return c;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  vector<Case> cc(tcc);
  F(i, 0, tcc) {
    l n, k; cin >> n >> k;
    cin >> cc[i].u;
    vd p(n);
    F(j, 0, n) cin >> p[j];
    cc[i].p = p;
    cc[i].n = n;
    cc[i].k = k;
    cc[i].id = i;
  }
  vector<double> answers(tcc);
  if (1) {
    F(i, 0, tcc) answers[i] = solve(cc[i]).answer;
  } else {
    vector<future<Case>> ff;
    F(i, 0, tcc) {
      auto a = async(launch::async, &solve, cc[i]);
      a.get();
      ff.emplace_back(move(a));
    };
    F(i, 0, tcc) answers[i] = ff[i].get().answer;
  }
  F(tc, 1, tcc + 1) {
    cout << "Case #" << tc << ": " << fixed << setprecision(9)
         << answers[tc - 1] << lf;
  }
}
