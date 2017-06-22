#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "number_bases"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include "number_bases.h"
#include "message.h"
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

void solve(istream& cin, ostream& cout) {
  l nodes = NumberOfNodes();
  l id = MyNodeId();
  bool master = id == 0;
  l n = GetLength();
  l interval = (n + nodes - 1) / nodes;
  l from = min(n, id * interval);
  l to = min(n, (id + 1) * interval);
  l p = to - from;
  if (p) {
    vl x(p);
    vl y(p);
    vl z(p);
    l m = 0;
    F(i, from, to) {
      x[i - from] = GetDigitX(i);
      y[i - from] = GetDigitY(i);
      z[i - from] = GetDigitZ(i);
    }
    l b = INF;
    l last = 0;
    F(i, 0, p) {
      m = max(m, max(x[i], max(y[i], z[i])));
      l t = x[i] + y[i] + last;
      if (t == z[i]) {
        last = 0;
        continue;
      }
      l nb = t - z[i];
      last = 1;
      if (b == INF) b = nb;
      if (b != nb) {
        b = -1;
        break;
      }
    }
    // prev = 0 -> last, base ; if prev = 1 -> last base
    PutLL(0, last);
    PutLL(0, b);

    last = 1;
    b = INF;
    F(i, 0, p) {
      l t = x[i] + y[i] + last;
      if (t == z[i]) {
        last = 0;
        continue;
      }
      l nb = t - z[i];
      last = 1;
      if (b == INF) b = nb;
      if (b != nb) {
        b = -1;
        break;
      }
    }
    PutLL(0, last);
    PutLL(0, b);
    PutLL(0, m);
  } else {
    PutLL(0, -1);
  }
  Send(0);

  if (not master) return;
  l b = INF;
  l last = 0;
  l m = 0;
  F(i, 0, nodes) {
    Receive(i);
    l l0 = GetLL(i);
    if (l0 == -1) break;
    l b0 = GetLL(i);
    l l1 = GetLL(i);
    l b1 = GetLL(i);
    m = max(m, GetLL(i));
    // cerr << l0 << ' ' << b0 << ' ' << l1 << ' ' << b1 << endl;
    l nb = (last ? b1 : b0);
    last = (last ? l1 : l0);
    if (b == INF) b = nb;
    if (nb != INF and b != nb) {
      b = -1; break;
    }
  }
  if (last or m >= b) b = -1;
  if (b == -1) {
    cout << "IMPOSSIBLE" << lf;
  } else if (b == INF) {
    cout << "NON-UNIQUE" << lf;
  } else {
    cout << b << lf;
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
