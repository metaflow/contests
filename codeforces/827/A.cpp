#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "A"
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
#define B(a,b,c) for (l a = l(c) - 1; a >= l(b); a--)

#if defined(LOCAL)
bool local = true;
#define L(x...) debug(x)
#else
bool local = false;
#define L(x, ...) (x)
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

using lll = tuple<l, l, l>;

void solve(istream& cin, ostream& cout) {
  l n;
  while (cin >> n) {
    string answer;
    vector<lll> parts;
    vector<string> values(n);
    l size = 0;
    F(i, 0, n) {
      l m;
      cin >> values[i] >> m;
      F(j, 0, m) {
        l x; cin >> x; x--;
        size = max(size, x + (l)values[i].size());
        parts.emplace_back(x, x + values[i].size(), i);
      }
    }
    answer.resize(size, 'a');
    sort(all(parts));
    l p = 0;
    for (auto z : parts) {
      p = max(p, get<0>(z));
      while (p < get<1>(z)) {
        answer[p] = values[get<2>(z)][p - get<0>(z)];
        p++;
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
