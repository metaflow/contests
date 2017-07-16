#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "thief"
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

const l MAXW = 301;

l value(l p, l a, vl& v, vl& s, l w) {
  l x = p / w - a / w - 1;
  if (x < 0 or x >= v.size()) return 0;
  return s[a] + v[x];
}

// finds lowest x: f(x) = true, x within [a, b), b if f(b - 1) = false
l binary_search_lower(l a, l b, function<bool(l)> f) {
  l count = b - a;
  while (count > 0) {
    l step = count / 2;
    l m = a + step;
    if (f(m)) {
      count = step;
    } else {
      a = m + 1;
      count -= step + 1;
    }
  }
  return a;
}

l overtakes(l a, l b, vl& v, vl& s, l w) {
  // a < b
  l mod = a % w;
  assert(a % w == b % w);
  return binary_search_lower(b / w - 1, (a + v.size()) / w, [&](l x ) {
      return value(x * w + mod, a, v, s, w) >= value(x * w + mod, b, v, s, w);
    }) * w + mod;
}

bool good(l a, l b, l c, vl& v, vl& s, l w) {
  // a > b > c
  return overtakes(c, a, v, s, w) < overtakes(b, a, v, s, w);
}

void solve(istream& cin, ostream& cout) {
  l N, K;
  cin >> N >> K;
  vl s(K + 1);
  vvl v(MAXW);
  F(i, 0, N) {
    l x, y; cin >> x >> y;
    v[x].emplace_back(y);
  }
  F(w, 1, MAXW) {
    l m = v[w].size();
    if (m == 0) continue;
    sort(all(v[w]), greater<l>());
    F(j, 1, v[w].size()) v[w][j] += v[w][j - 1];
    F(j, 0, w) {
      l p = K - j;
      deque<l> q;
      F(k, 0, m) {
        l t = p - k * w;
        if (t < 0) break;
        while (q.size() > 1 and
               not good(q[q.size() - 2], q[q.size() - 1], t, v[w], s, w)) {
          q.pop_back();
        }
        q.push_back(t);
      }
      while (p > 0) {
        l t = p - m * w;
        if (t >= 0) {
          while (q.size() > 1 and
                 not good(q[q.size() - 2], q[q.size() - 1], t, v[w], s, w)) {
            q.pop_back();
          }
          q.push_back(t);
        }
        while (q.size() > 1 and
               value(p, q[0], v[w], s, w) <= value(p, q[1], v[w], s, w)) {
          q.pop_front();
        }
        if (not q.empty()) s[p] = max(s[p], value(p, q.front(), v[w], s, w));
        p -= w;
      }
    }
  }
  F(i, 0, K) {
    if (i) cout << ' ';
    cout << s[i + 1];
  }
  cout << lf;
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
