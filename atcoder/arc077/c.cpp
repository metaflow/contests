#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "c"
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

void solve(istream& cin, ostream& cout) {
  l n, m;
  while (cin >> n >> m) {
    vll events;
    l last; cin >> last;
    l worst = 0;
    F(i, 0, n - 1) {
      l x; cin >> x;
      l to = x;
      if (to < last) to += m;
      worst += to - last;
      if (to - last > 1) {
        events.emplace_back(last + 1, 0); // add to active
        events.emplace_back(to, to - last - 1); // how much to remove
        events.emplace_back(last + 1 + m, 0); // add to active
        events.emplace_back(to + m, to - last - 1); // how much to remove
      }
      last = x;
    }
    sort(all(events));
    l active = 0;
    l bonus = 0;
    l answer = worst;
    l j = 0;
    l p = 0;
    while (j < events.size()) {
      l x = events[j].first;
      bonus += active * (x - p);
      answer = min(answer, worst - bonus);
      p = x;
      while (j < events.size() and events[j].first == x) {
        if (events[j].second) {
          bonus -= events[j].second;
          active--;
        } else {
          active++;
        }
        j++;
      }
    }
    cout << answer << lf;
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
