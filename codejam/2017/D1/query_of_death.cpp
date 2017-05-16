#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif
#include "query_of_death.h"
#include <message.h>

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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l me = MyNodeId();
  l L = GetLength();
  if (me) {
    l N = NumberOfNodes() - 1;
    l p = (L + N - 1) / N;
    l broken = 0;
    l sum = 0;
    l lo = (me - 1) * p;
    l hi = min(L, me * p);
    vl v(max((l)1, hi - lo + 1));
    F(i, lo, hi) {
      v[i - lo] = GetValue(i);
      sum += v[i - lo];
    }
    bool ok = true;
    if (hi - lo < 100) {
      F(j, 0, 100) {
        F(i, lo, hi) ok = ok and v[i - lo] == GetValue(i);
        if (not ok) break;
      }
    } else {
      F(i, lo, hi) ok = ok and v[i - lo] == GetValue(i);
    }
    if (not ok) broken = 1;
    PutLL(0, broken);
    PutLL(0, lo);
    PutLL(0, hi);
    PutLL(0, sum);
    Send(0);
    if (broken)
      return 0;
    Receive(0);
    lo = GetLL(0);
    hi = GetLL(0);
    broken = -1;
    F(i, lo, hi) {
      l x = GetValue(i);
      bool ok = true;
      F(j, 0, 100) ok = ok and GetValue(i) == x;
      if (not ok) {
        broken = i;
        break;
      }
    }
    PutLL(0, broken);
    Send(0);
    return 0;
  }
  l answer = 0;
  l N = NumberOfNodes();
  l lo, hi, broken_node;
  F(i, 1, N) {
    Receive(i);
    l b = GetLL(i);
    if (b) {
      broken_node = i;
      lo = GetLL(i);
      hi = GetLL(i);
      GetLL(i); // sum
      continue;
    }
    GetLL(i); // lo
    GetLL(i); // hi
    answer += GetLL(i);
  }
  l active = N - 2;
  l part = hi - lo;
  part = (part + active - 1) / active;
  l j = 0;
  F(i, 1, N) {
    if (i == broken_node) continue;
    PutLL(i, lo + part * j);
    PutLL(i, min(L, lo + part * (j + 1)));
    Send(i);
    j++;
  }
  l broken = -1;
  F(i, 1, N) {
    if (i == broken_node) continue;
    Receive(i);
    l x = GetLL(i);
    if (x != -1) broken = x;
  }
  F(i, lo, hi) {
    if (i != broken) answer += GetValue(i);
  }
  answer += GetValue(broken);
  cout << answer << endl;
}
