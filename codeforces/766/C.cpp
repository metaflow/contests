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

const l MOD = e9 + 7;
vl rs(26);
vl dp;
vl s;

l f1(l n) {
  if (n == -1) return 1;
  l& result = dp[n];
  if (result == -1) {
    result = 0;
    l r = rs[s[n]];
    for (l i = n; i >= 0; i--) {
      r = min(rs[s[i]], r);
      if (r < (n - i + 1)) break;
      result = (result + f1(i - 1)) % MOD;
    }
  }
  return result;
}

l f2(l n) {
  if (n == -1) return 0;
  l& result = dp[n];
  if (result == -1) {
    result = 0;
    l r = rs[s[n]];
    for (l i = n; i >= 0; i--) {
      r = min(rs[s[i]], r);
      if (r < (n - i + 1)) break;
      result = max(result, n - i + 1);
      result = max(result, f2(i - 1));
    }
  }
  return result;
}

l f3(l n) {
  if (n == -1) return 0;
  l& result = dp[n];
  if (result == -1) {
    result = INF;
    l r = rs[s[n]];
    for (l i = n; i >= 0; i--) {
      r = min(rs[s[i]], r);
      if (r < (n - i + 1)) break;
      result = min(result, 1 + f3(i - 1));
    }
  }
  return result;
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  string word;
  while (cin >> n >> word) {
    for (l i = 0; i < (l)rs.size(); i++) cin >> rs[i];
    s.resize(n);
    for (l i = 0; i < n; i++) s[i] = word[i] - 'a';
    dp.resize(n);
    fill(dp.begin(), dp.end(), -1);
    cout << f1(n - 1) << '\n';
    fill(dp.begin(), dp.end(), -1);
    cout << f2(n - 1) << '\n';
    fill(dp.begin(), dp.end(), -1);
    cout << f3(n - 1) << '\n';
  }
}
