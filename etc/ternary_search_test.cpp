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
const double EPS = 1e-10;
const l e0=1, e3=1000, e5=100000, e6=e3*e3, e7=10*e6, e8=10*e7, e9=10*e8;
const char lf = '\n';
#define ALL(x) begin(x), end(x)
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


l ternary_search_min(l from, l to, function<l(l)> f) {
  l L = from, R = to;
  l rl = f(L), rr = f(R);
  while (1) {
    if (R - L < 2) {
      if (rl < rr) return L;
      return R;
    }
    if (R - L == 2) {
      l t = f(L + 1);
      if (t < rl) {
        if (t < rr) return L + 1;
        return R;
      } else {
        if (rl < rr) return L;
        return R;
      }
    }
    l m1 = L + (R - L) / 3;
    l m2 = L + 2 * (R - L) / 3;
    vl v = {rl, f(m1), f(m2), rr};
    l x = 0;
    F(i, 1, 4) if (v[i] < v[x]) x = i;
    if (x < 2) { R = m2; rr = v[2]; }
    else { L = m1; rl = v[1]; }
  }
  assert(false);
  return 0;
}

l search_brute(l from, l to, function<l(l)> f) {
  l result = from;
  F(i, from + 1, to + 1) {
    if (f(i) < f(result)) result = i;
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  F(i, 0, 1000) {
    l from = random_in_range(0, 100);
    l to = random_in_range(from, from + 100);
    l a = random_in_range(-10, 0);
    l b = random_in_range(-100, 100);
    l c = random_in_range(-100, 100);
    auto f = [&](l x) {
      return a * x * x + b * x + c;
    };
    l r1 = search_brute(from, to, f);
    l r2 = ternary_search_min(from, to, f);
    if (f(r1) != f(r2)) {
      cout << "a " << a << " b " << b << " c " << c << endl
           << r1 << ' ' << r2 << endl;
      return 1;
    }
  }
  cout << "PASSED" << lf;
}
