#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif
#include "pancakes.h"
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
  l answer = 0;
  bool master = MyNodeId() == 0;
  l N = NumberOfNodes();
  l S = GetStackSize();
  l part = (S + (N - 1)) / N;
  F(i, MyNodeId() * part, min((MyNodeId() + 1) * part, S - 1)) {
    if (GetStackItem(i) > GetStackItem(i + 1)) answer++;
  }
  if (master) {
    F(i, 1, NumberOfNodes()) {
      Receive(i);
      answer += GetLL(i);
    }
    cout << answer + 1 << lf;
  } else {
    PutLL(0, answer);
    Send(0);
  }
}
