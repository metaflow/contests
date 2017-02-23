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

const l MAX = 101;
const l Z = 26;
const l MOD = e9 + 7;
const l MZ = MAX * Z;
l M[MAX * Z][MAX];

l divup(l a, l b) {
  return (a / b) + ((a % b) ? 1 : 0);
}

l dp(l sum, l len) {
  if (sum == 0) return 1;
  if (sum > len * (Z - 1)) return 0;
  l& r = M[sum][len];
  if (r == 0) {
    for (l i = 0; i < min(Z, sum + 1); i++)
      r += dp(sum - i, len - 1);
    r %= MOD;
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  fill(&M[0][0], &M[MAX * Z][0], 0);
  while (cin >> n) {
    for (l tc = 0; tc < n; tc++) {
      string s; cin >> s;
      l sum = 0;
      for (l i = 0; i < s.size(); i++) sum += (s[i] - 'a');
      cout << (dp(sum, s.size()) - 1) << '\n';
    }
  }
}
