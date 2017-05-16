#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif
#include <message.h>
#include "todd_and_steven.h"

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

// finds lowest x: f(x) = true, x within [a, b), b if f(b - 1) = false
l binary_search_lower(l a, l b, function<bool(l)> f) {
  l count = b - a;
  while (count > 0) {
    l step = count / 2;
    l m = a + step;
    if (not f(m)) {
      a = m + 1;
      count -= step + 1;
    } else {
      count = step;
    }
  }
  return a;
}

ll get_affected(l v) {
  l t = binary_search_lower(0, GetToddLength(), [&](l x) {
      return GetToddValue(x) >= v;
    });
  l s = binary_search_lower(0, GetStevenLength(), [&](l x) {
      return GetStevenValue(x) >= v;
    });
  return make_pair(t, s);
}

const l MOD = e9 + 7;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l N = NumberOfNodes();
  l me = MyNodeId();
  ll to = make_pair(GetToddLength(), GetStevenLength());
  if (me != N - 1) {
    l total = GetToddLength() + GetStevenLength();
    l part = (total + N - 1) / N;
    l m = max(GetToddValue(GetToddLength() - 1),
              GetStevenValue(GetStevenLength() - 1));
    l target = part * (me + 1);
    l v = binary_search_lower(1, m, [&](l x) {
        ll affected = get_affected(x);
        return affected.first + affected.second + 2 >= target;
      });
    to = get_affected(v);
    to.first = min(to.first, GetToddLength());
    to.second = min(to.second, GetStevenLength());
    PutLL(me + 1, to.first);
    PutLL(me + 1, to.second);
    Send(me + 1);
  }
  l todd = 0;
  l steven = 0;
  if (me) {
    Receive(me - 1);
    todd = GetLL(me - 1);
    steven = GetLL(me - 1);
  }
  l answer = 0;
  // cout << todd << ' ' << to.first << ' ' << steven << ' ' << to.second << endl;
  while (todd < to.first or steven < to.second) {
    l x = 0;
    if (steven >= to.second or
        (todd < to.first and GetToddValue(todd) < GetStevenValue(steven))) {
      x = GetToddValue(todd);
      todd++;
    } else {
      x = GetStevenValue(steven);
      steven++;
    }
    // cout << x << ' ' << (todd + steven - 1) << ' ';
    x = x ^ (todd + steven - 1);
    // cout << x << endl;
    answer = (answer + x) % MOD;
  }
  if (me) {
    PutLL(0, answer);
    Send(0);
    return 0;
  }
  // cout << answer << endl;
  F(i, 1, N) {
    Receive(i);
    l x = GetLL(i);
    // cout << "got " << i << ' ' << x << endl;
    answer = (answer + x) % MOD;
  }
  cout << answer << lf;
}
