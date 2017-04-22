#include <bits/stdc++.h>

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

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

l gcd(l a, l b) {
  while (b) { l t = b; b = a % b; a = t; }
  return a;
}

l lcm(l a, l b) { return a * b / gcd(a, b); }

ll solve(l a, l b, l c, l d) {
  l q = lcm(b, d);
  l p = lcm(a * q / b, c * q / d);
  l g = gcd(p, q);
  return make_pair(p / g, q / g);
}

ll solve_brute(l a, l b, l c, l d) {
  for (l k = 1; k < 1000000; k++) {
    l p = k * a; l q = b;
    if ((p * d) % (q * c) == 0) {
      l g = gcd(p, q);
      return make_pair(p / g, q / g);
    }
  }
  return make_pair(1, 0);
}

default_random_engine source(chrono::system_clock::now().time_since_epoch().count());

// [a, b)
l random_in_range(l a, l b) {
  return uniform_int_distribution<l>(a, b - 1)(source);
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


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  F(i, 0, 10000) {
    l a = random_in_range(1, 1000);
    l b = random_in_range(1, 1000);
    l g = gcd(a, b);
    a /= g; b /= g;
    l c = random_in_range(1, 1000);
    l d = random_in_range(1, 1000);
    g = gcd(c, d);
    c /= g; d /= g;
    auto p = solve(a, b, c, d);
    auto e = solve_brute(a, b, c, d);
    if (p != e) {
      LOG << a << ' ' << b << ' ' << c << ' ' << d << lf
          << p.first << ' ' << p.second << lf
          << e.first << ' ' << e.second << lf;
      return 1;
    }
  }
  l tcc;
  cin >> tcc;
  while (tcc--) {
    l a, b, c, d;
    cin >> a >> b >> c >> d;
    auto p = solve(a, b, c, d);
    cout << p.first << ' ' << p.second << lf;
  }
}
