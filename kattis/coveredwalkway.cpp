#include <bits/stdc++.h>
#if defined(LOCAL)
#include "prettyprint.h"
#endif

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
bool local = true;
#else
bool local = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(local) ? (void) 0 : VoidStream() & cerr

l cost(ll solution, l x) {
  l d = solution.first - x;
  return solution.second + d * d;
}

l brute(vl& v, l c) {
  l n = v.size();
  vl dp(n, INF);
  dp[0] = c;
  F(i, 1, n) F(j, 0, i)
    dp[i] = min(dp[i], cost(make_pair(v[j], dp[j]), v[i - 1]) + c);
  l best = INF;
  F(i, 0, n) {
    l t = cost(make_pair(v[i], dp[i]), v[n - 1]);
    // LOG << v[i] << ' ' << dp[i] << endl;
    best = min(best, t);
  }
  return best;
}

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

// a.first < b.first
l overtakes(ll a, ll b) {
  l lo = b.first;
  l hi = b.first;
  while (cost(a, hi) < cost(b, hi)) {
    lo = hi + 1;
    hi *= 2;
  }
  return binary_search_lower(lo, hi, [&](const l x) {
      return cost(a, x) >= cost(b, x);
    });
}

l solve(vl& v, l c) {
  l n = v.size();
  deque<ll> q; // (start, cost) // leftmost is the best so far
  q.push_back(make_pair(v[0], c));
  F(i, 1, n) {
    l x = v[i];
    ll a = make_pair(x, cost(q.front(), v[i - 1]) + c);
    while (q.size() > 1) {
      l r = overtakes(q[q.size() - 2], a);
      l t = overtakes(q[q.size() - 2], q.back());
      // LOG << "rt " << r << ' ' << t << endl;
      if (r >= t and cost(q.back(), x) < a.second) break;
      // LOG << "pop" << endl;
      q.pop_back();
    }
    q.emplace_back(a);
    while (q.size() > 1 and (cost(q[0], x) >= cost(q[1], x))) q.pop_front();
    // LOG << q << endl;
    // if (local) for (auto p : q) LOG << cost(p, x) << ' ';
    // LOG << endl;
  }
  return cost(q.front(), v.back());
}

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
}

double random_double() {
  return uniform_real_distribution<double>(0, 1)(source);
}

bool random_bool() {
  return random_in_range(0, 2) == 1;
}

string random_string(int length) {
  string s = "";
  string an = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < length; i++) {
    s += an[random_in_range(0, an.size())];
  }
  return s;
}

void test() {
  local = false;
  F(n, 1, 10)
    F(tcc, 0, 100000) {
    l c = random_in_range(0, 1000);
    vl v(n);
    l last = 0;
    F(i, 0, n) {
      last += random_in_range(1, 100);
      v[i] = last;
    }
    l b = brute(v, c);
    l s = solve(v, c);
    if (b != s) {
      cout << b << ' ' << s << endl;
      cout << n << ' ' << c << endl;
      for (l i : v) cout << i << endl;
      return;
    }
  }
  cout << "OK" << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // test();
  // return 0;
  l n, c;
  while (cin >> n >> c) {
    vl v(n);
    F(i, 0, n) {
      cin >> v[i];
    }
    LOG << brute(v, c) << endl;
    cout << solve(v, c) << lf;
    // break;
  }
}
