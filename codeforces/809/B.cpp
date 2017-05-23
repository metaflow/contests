#include <bits/stdc++.h>
// #undef LOCAL
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
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

l n;
l ask_count = 0;
#ifdef LOCAL
vb v;
bool ask(l x, l y) {
  if (ask_count >= 60) {
    cout << v << endl;
  }
  assert(ask_count < 60);
  ask_count++;
  x--; y--;
  l dx = INF;
  F(i, 0, n) if (v[i]) dx = min(dx, abs(x - i));
  l dy = INF;
  F(i, 0, n) if (v[i]) dy = min(dy, abs(y - i));
  return dx <= dy;
}
#else
bool ask(l x, l y) {
  assert(ask_count < 60);
  ask_count++;
  cout << "1 " << x << ' ' << y << endl;
  string s; cin >> s;
  return s == "TAK";
}
#endif

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

l search(l x, l y) {
  while (x < y) {
    l m = (x + y) / 2;
    if (ask(m, m + 1)) {
      y = m;
    } else {
      x = m + 1;
    }
  }
  return x;
}

ll solve() {
  ask_count = 0;
  l d1 = search(1, n);
  l d2 = search(min(n, d1 + 1), n);
  if (d2 != d1 and ask(d2, d1)) return make_pair(d1, d2);
  return make_pair(d1, search(1, d1 - 1));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l k;
#ifdef LOCAL
  F(tc, 0, 10000) {
    n = random_in_range(2, 1000);
    v.resize(n);
    F(i, 0, n) v[i] = false;
    l a = random_in_range(0, n - 1);
    l b = random_in_range(a + 1, n);
    v[a] = true;
    v[b] = true;
    k = random_in_range(0, 10);
    F(i, 0, k) v[random_in_range(0, n)] = true;
    ll s = solve();
    if (v[s.first - 1] and v[s.second - 1]) continue;
    cout << a << ' ' << b << endl;
    cout << s.first - 1 << ' ' << s.second - 1 << endl;
    cout << "!" << endl;
    return 1;
  }
  cout << "PASSED" << endl;
#else
  cin >> n >> k;
  ll s = solve();
  cout << "2 " << s.first << ' ' << s.second << endl;
#endif
}
