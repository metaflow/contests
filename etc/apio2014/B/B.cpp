#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "B"
const double _max_double_error = 1e-9;
#define MEMORY 128
#define TIME 2
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

struct Sol {
  l a, b, i;
  l at(l x) {
    return a * x + b;
  }
};

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

l overcomes(Sol a, Sol b) {
  return binary_search_lower(0, INF, [&](l x) {
      return b.at(x) >= a.at(x);
    });
}

bool ordered(Sol a, Sol b, Sol c) {
  return (a.b - b.b) * (c.a - b.a) < (b.b - c.b) * (b.a - a.a);
  // return overcomes(a, b) < overcomes(b, c);
}

void solve(istream& cin, ostream& cout) {
  l N, K;
  cin >> N >> K;
  vl acc(N + 1), v(N);
  F(i, 0, N) {
    cin >> v[i];
    acc[i + 1] = acc[i] + v[i];
  }
  vl w(N);
  vvi splits(K, vi(N));
  F(k, 0, K) {
    vl u(N);
    deque<Sol> q;
    F(i, 0, N) {
      l x = acc[i + 1];
      while (q.size() > 1 and q[0].at(x) <= q[1].at(x)) q.pop_front();
      if (not q.empty()) {
        u[i] = q.front().at(x);
        splits[k][i] = q.front().i;
      }
      Sol s;
      s.a = x;
      s.b = w[i] - x * x;
      s.i = i;
      while (q.size() > 1 and not ordered(q[q.size() - 2], q[q.size() - 1], s)) {
        q.pop_back();
      }
      q.emplace_back(s);
    }
    swap(u, w);
  }
  cout << w[N - 1] << lf;
  vl ss(K);
  l p = N - 1;
  B(i, K - 1, -1) {
    p = ss[i] = splits[i][p];
  }
  F(i, 0, K) {
    if (i) cout << ' ';
    cout << ss[i] + 1;
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
