#if defined(LOCAL)
// #define RANDOM_TEST
#define PROBLEM_NAME "nanobots"
const double _max_double_error = 1e-9;
#include "testutils.h"
#endif
#include <bits/stdc++.h>
#include "nanobots.h"
#include "message.h"

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

const l MOD = e9 + 7;

struct Query {
  l x, y, r;
};

struct Sub {
  l value;
  Query q1, q2;
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

l MAX;
bool exp(l x, l y) {
  if (x > MAX or y > MAX) return false;
  return Experiment(x, y) == 'T';
}

Sub f(Query q) {
  Sub s;
  if (q.r < 2) return s;
  l r = max(binary_search_lower(1, q.r, [&](l x) {
        return not exp(q.x + x, q.y + x);
      }) - 1, (l)0);
  s.value = (r * r) % MOD;
  s.q1 = q;
  s.q2 = q;
  s.q1.x += r; s.q1.r = r + 1;
  s.q2.y += r; s.q2.r = r + 1;
  return s;
}

l full(Query q) {
  if (q.r < 2) return 0;
  auto s = f(q);
  l x = s.value;
  x += full(s.q1);
  x += full(s.q2);
  return x % MOD;
}


void solve(istream& cin, ostream& cout) {
  l id = MyNodeId();
  l nodes = NumberOfNodes();
  MAX = GetRange();
  l answer = 0;
  if (id == 0) {
    queue<Query> q;
    Query s; s.x = 0; s.y = 0; s.r = GetRange() + 1;
    q.emplace(s);
    while (not q.empty() and q.size() < nodes) {
      auto p = q.front(); q.pop();
      Sub sol = f(p);
      answer = (answer + sol.value) % MOD;
      if (sol.q1.r) q.emplace(sol.q1);
      if (sol.q2.r) q.emplace(sol.q2);
    }
    F(i, 0, nodes) {
      Query t;
      t.x = 0; t.y = 0; t.r = 0;
      if (not q.empty()) {
        t = q.front();
        q.pop();
      }
      PutLL(i, t.x);
      PutLL(i, t.y);
      PutLL(i, t.r);
      Send(i);
    }
  }

  Receive(0);
  Query s;
  s.x = GetLL(0);
  s.y = GetLL(0);
  s.r = GetLL(0);
  l a = full(s);
  PutLL(0, a);
  Send(0);
  if (id) return;
  F(i, 0, nodes) {
    Receive(i);
    answer = (answer + GetLL(i)) % MOD;
  }
  cout << answer << lf;
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
