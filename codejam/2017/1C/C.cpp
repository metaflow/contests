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
  auto p = c.p;
  auto n = c.n;
  auto k = c.k;
  auto u = c.u;
  sort(all(p));
  l start = n - k;
  l j = start;
  double sum = p[j];
  j++;
  while (j < n and ((sum + u) / j > p[j])) { sum += p[j]; j++; }
  l q = j - start;
  double s = min(u, q - sum);
  F(i, start, j) p[i] = (sum + s) / q;
  double v = prob(p, k);

  p = c.p;
  sort(all(p));
  start = 0;
  j = 0;
  sum = p[j];
  j++;
  while (j < n and ((sum + u) / j > p[j])) { sum += p[j]; j++; }
  q = j - start;
  s = min(u, q - sum);
  F(i, start, j) p[i] = (sum + s) / q;
  v = max(v, prob(p, k));

  c.answer = v;
  return c;
}

bool equal_double(double x, double y) {
  if (abs(x - y) < EPS) return true;
  // Is x or y too close to zero?
  if (abs(x) < EPS || abs(y) < EPS) return false;
  // Check relative precision.
  return (abs((x - y) / x) < EPS) && (abs((x - y) / y) < EPS);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  if (0) {
    vector<vvd> best_p(1000);
    vd best(1000);
    F(i, 0, 101) F(j, 0, 101) F(k, 0, 61) {
      vd p; p.emplace_back(i); p.emplace_back(j); p.emplace_back(k + 40);
      for (auto& t : p) t /= 100;
      double v = prob(p, 2);
      if (equal_double(best[i + j + k], v)) {
        best_p[i + j + k].emplace_back(p);
      } else if (v > best[i + j + k]) {
        best[i + j + k] = v;
        best_p[i + j + k].clear();
        best_p[i + j + k].emplace_back(p);
      }
    }
    F(i, 0, 301) {
      LOG << i << ":" << best[i] << endl;
      for (auto p : best_p[i]) LOG << p << endl;
    }
    return 0;
  }


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
