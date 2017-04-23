// #define ONLINE_JUDGE
#include <bits/stdc++.h>
#if !defined(ONLINE_JUDGE)
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

const l R = 1;
const l B = 2;
const l Y = 4;
const l RB = R | B;
const l RY = R | Y;
const l BY = B | Y;

bool dfs(vl v, l p, vl cc) {
  if (p == -1) return true;
  l n = v.size();
  l j = (p + 1) % n;
  l k = (p - 1 + n) % n;
  l t = v[j] | v[k];
  F(i, 0, 8) {
    if (cc[i] and ((i & t) == 0)) {
      auto c = cc;
      c[i]--;
      v[p] = i;
      if (dfs(v, p - 1, c)) return true;
    }
  }
  return false;
}

bool solve(vl& v, l p, vl& cc) {
  if (p == -1) return true;
  l n = v.size();
  v.resize(0);
  if (cc[B]) {
    v.emplace_back(B);
    cc[B]--;
  }
  while (cc[RY] and (v.empty() or v.back() != RY)) {
    v.emplace_back(RY);
    cc[RY]--;
    if (cc[B]) {
      v.emplace_back(B);
      cc[B]--;
    }
  }
  if (cc[RY]) return false;

  if (cc[R]) {
    v.emplace_back(R);
    cc[R]--;
  }
  while (cc[BY] and (v.empty() or v.back() != BY)) {
    v.emplace_back(BY);
    cc[BY]--;
    if (cc[R]) {
      v.emplace_back(R);
      cc[R]--;
    }
  }
  if (cc[BY]) return false;

  if (cc[Y]) {
    v.emplace_back(Y);
    cc[Y]--;
  }
  while (cc[RB] and (v.empty() or v.back() != RB)) {
    v.emplace_back(RB);
    cc[RB]--;
    if (cc[Y]) {
      v.emplace_back(Y);
      cc[Y]--;
    }
  }
  if (cc[RB]) return false;

  while (cc[R] + cc[B] + cc[Y]) {
    l t = 0;
    vl next;
    l m = v.size();
    F(i, 0, m) {
      l j = (i + 1) % m;
      next.emplace_back(v[i]);
      F(k, 0, 8) {
        if (not cc[k]) continue;
        if ((v[i] & k) == 0 and cc[v[i]]) {
          next.emplace_back(k);
          cc[k]--;
          next.emplace_back(v[i]);
          cc[v[i]]--;
          t++;
          break;
        }
        if (cc[k] and (v[i] & k) == 0 and (v[j] & k) == 0) {
          next.emplace_back(k);
          cc[k]--;
          t++;
          break;
        }
      }
    }
    if (t == 0) return false;
    swap(v, next);
  }
  F(i, 0, n) {
    l j = (i + 1) % n;
    if (v[i] & v[j]) return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  if (0) {
    F(i, 0, 100) {
      LOG << '.' << endl;
      vl c(8);
      c[R] = random_in_range(0, 5);
      c[B] = random_in_range(0, 5);
      c[Y] = random_in_range(0, 5);
      c[RB] = random_in_range(0, 5);
      c[RY] = random_in_range(0, 5);
      c[BY] = random_in_range(0, 5);
      l n = accumulate(all(c), 0);
      vl v(n), w(n);
      auto y = c;
      auto cc = c;
      if (solve(v, n - 1, y) != dfs(w, n - 1, c)) {
        cout << "failed " << cc << endl;
        return 1;
      }
    }
    cout << "PASSED" << lf;
    return 0;
  }
  l tcc; cin >> tcc;
  F(tc, 1, tcc + 1) {
    l n;
    vl c(8);
    cin >> n >> c[R] >> c[RY] >> c[Y] >> c[BY] >> c[B] >> c[RB];
    vl v(n);
    cout << "Case #" << tc << ": ";
    if (solve(v, n - 1, c)) {
      for (auto i : v) {
        switch (i) {
        case R: cout << 'R'; break;
        case Y: cout << 'Y'; break;
        case B: cout << 'B'; break;
        case RB: cout << 'V'; break;
        case BY: cout << 'G'; break;
        case RY: cout << 'O'; break;
        }
      }
      cout << lf;
    } else {
      cout << "IMPOSSIBLE" << lf;
    }
  }
}
