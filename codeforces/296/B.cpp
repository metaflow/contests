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
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

const l MOD = e9+7;

l mult(l a, l b) { return (a * b) % MOD; }

l less_or_equal(const string& s, const string& w) {
  l r = 1;
  for (l i = 0; i < s.size(); i++) {
    if (s[i] != '?' and w[i] != '?') {
      if (s[i] > w[i]) return 0;
      continue;
    }
    if (s[i] != '?') {
      r = mult(r, 10 - (s[i] - '0'));
      continue;
    }
    if (w[i] != '?') {
      r = mult(r, (w[i] - '0') + 1);
      continue;
    }
    r = mult(r, 55);
  }
  return r;
}

l equal(const string& s, const string& w) {
  l r = 1;
  for (l i = 0; i < s.size(); i++) {
    if (s[i] == w[i]) {
      if (s[i] == '?') r = mult(r, 10);
    } else {
      if (s[i] != '?' and w[i] != '?') return 0;
    }
  }
  return r;
}

l total(const string& s) {
  l r = 1;
  for (char c : s) if (c == '?') r = mult(r, 10);
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    string s, w;
    cin >> s >> w;
    cout << (mult(total(s), total(w)) - less_or_equal(s, w) - less_or_equal(w, s) + equal(s, w) + MOD) % MOD << '\n';
  }
}
