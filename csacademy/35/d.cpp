#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "d"
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

vl split(l n) {
  vl v;
  while (n) {
    v.emplace_back(n % 10);
    n /= 10;
  }
  return v;
}

l join(vl v) {
  l a = 0;
  l m = 1;
  for (auto i : v) {
    a += i * m;
    m *= 10;
  }
  return a;
}

vl next(vl& v) {
  vl r = v;
  l i = 0;
  l n = v.size();
  while (i < n) {
    if (r[i] % 2 == 0) {
      r[i]++;
      F(j, 0, i) r[j] = 1;
      break;
    }
    i++;
  }
  return r;
}

vl prev(vl& v) {
  vl r = v;
  l i = 0;
  l n = v.size();
  while (i < n) {
    if (r[i] % 2 == 0) {
      F(j, 0, i) r[j] = 9;
      if (r[i] == 0) {
        if (i + 1 < n) {
          r[i] = 9;
          r[i + 1]--;
          if (r[i + 1] % 2) break;
        }
      } else {
        r[i]--;
        break;
      }
    }
    i++;
  }
  return r;
}

void solve(istream& cin, ostream& cout) {
  l n;
  while (cin >> n) {
    vl v = split(n);
    l a = (join(next(v))) - n;
    l b = n - (join(prev(v)));
    l answer = a * b;
    if (answer == 0) answer = -1;
    cout << (answer) << lf;
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
