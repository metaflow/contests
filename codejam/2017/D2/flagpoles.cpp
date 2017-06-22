#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "flagpoles"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include "flagpoles.h"
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
using lll = tuple<l,l,l>;
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
  l n = GetNumFlagpoles();
  l interval = (n + nodes - 1) / nodes;
  bool single_node = interval < 3;
  if (not master and single_node) return;
  if (single_node) interval = n;
  l from = max((l)0, min(n, interval * id) - 1);
  l to = min(n, interval * (id + 1) + 1);
  l best = 1;
  l left, right; // len
  if (from + 1 < to) {
    l j = from;
    l d = GetHeight(j + 1) - GetHeight(j);
    j++;
    while (j + 1 < to and GetHeight(j + 1) - GetHeight(j) == d) j++;
    left = j - from + 1;

    j = to - 1;
    d = GetHeight(j) - GetHeight(j - 1);
    j--;
    while (j > from and GetHeight(j) - GetHeight(j - 1) == d) j--;
    right = to - j;

    j = from;
    d = GetHeight(from + 1) - GetHeight(from);
    l run = 2;
    F(i, from + 1, to - 1) {
      l x = GetHeight(i + 1) - GetHeight(i);
      if (x != d) {
        best = max(best, run);
        run = 1;
        d = x;
      }
      run++;
    }
    best = max(best, run);
  }
  PutLL(0, to - from);
  PutLL(0, best);
  PutLL(0, left);
  PutLL(0, right);
  Send(0);
  if (not master) return;
  l d = 0;
  l run = 2;
  F(i, 0, nodes) {
    Receive(i);
    l t = GetLL(i);
    l b = GetLL(i);
    best = max(best, b);
    l left_cont = GetLL(i);
    l new_run = GetLL(i);
    run += left_cont - 2;
    best = max(best, run);
    if (left_cont != t) run = new_run;
    if (single_node) break;
  }
  cout << best << lf;
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
