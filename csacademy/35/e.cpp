#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "e"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
using mll = unordered_map<l, l>;
const l INF = numeric_limits<int>::max();
const double EPS = 1e-10; static constexpr auto PI = acos(-1);
const l e0=1, e3=1000, e5=100000, e6=10*e5, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define all(x) begin(x), end(x)
#define F(a,b,c) for (l a = l(b); a < l(c); a++)
#define B(a,b,c) for (l a = l(b); a > l(c); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

bool fill(vvl& M) {
  l n = M.size();
  l m = M[0].size();
  l mj = 0;
  F(i, 0, n) {
    l j = 0;
    l t = i;
    while (j < m and t) {
      M[i][j] = t % 2;
      mj = max(mj, j);
      t /= 2;
      j++;
    }
    if (t) return false;
  }
  mj++;
  l k = 0;
  while (mj < m) {
    M[k][mj] = 1;
    mj++;
    k++;
  }
  return true;
}

void output(vvl& answer, ostream& cout) {
  l n = answer.size();
  l m = answer[0].size();
  F(i, 0, n) {
    F(j, 0, m) cout << answer[i][j];
    cout << lf;
  }
}

void solve(istream& cin, ostream& cout) {
  l n, m;
  while (cin >> n >> m) {
    vvl rb, cb;
    unordered_map<l, l> ri, ci;
    F(i, 0, n) {
      l x; cin >> x;
      if (ri.count(x) == 0) {
        l t = ri.size();
        ri[x] = t;
        rb.resize(ri.size());
      }
      rb[ri[x]].emplace_back(i);
    }
    F(i, 0, m) {
      l x; cin >> x;
      if (ci.count(x) == 0) {
        l t = ci.size();
        ci[x] = t;
        cb.resize(ci.size());
      }
      cb[ci[x]].emplace_back(i);
    }
    bool inverse = ri.size() < ci.size();
    if (inverse) {
      swap(ri, ci);
      swap(rb, cb);
      swap(n, m);
    }
    vvl pp(ri.size(), vl(ci.size()));
    if (fill(pp)) {
      if (not inverse) {
        vvl answer(n, vl(m));
        F(i, 0, ri.size()) F(j, 0, ci.size()) {
          for (auto const k : rb[i])
            for (auto const p : cb[j]) answer[k][p] = pp[i][j];
        }
        output(answer, cout);
      } else {
        vvl answer(m, vl(n));
        F(i, 0, ri.size()) F(j, 0, ci.size()) {
          for (auto const k : rb[i])
            for (auto const p : cb[j]) answer[p][k] = pp[i][j];
        }
        output(answer, cout);
      }
    } else {
      cout << -1 << lf;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
