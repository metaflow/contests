#if defined(LOCAL)
#define RANDOM_TEST
#define PROBLEM_NAME "A"
const double _max_double_error = 1e-9;
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

l dfs(vl& a, l i, vl& b, l j, vl& freq, vvl& dp) {
  l n = a.size();
  if (j == n and i == n) return 0;
  l r = dp[i][j];
  if (r == -1) {
    r = INF;
    if (j == n) {
      if (freq[a[i]] == 0) return r;
      freq[a[i]]--;
      return dfs(a, i + 1, b, j, freq, dp);
    }
    if (a[i] == b[j]) return r = dfs(a, i + 1, b, j + 1, freq, dp);
    if (freq[a[i]]) {
      freq[a[i]]--;
      r = dfs(a, i + 1, b, j, freq, dp);
      freq[a[i]]++;
    }
    freq[b[j]]++;
    r = min(r, 1 + dfs(a, i, b, j + 1, freq, dp));
  }
  return r;
}

void solve(istream& cin, ostream& cout) {
  string s, q;
  while (cin >> s >> q) {
    l n = s.size();
    vl a(n), b(n);
    F(i, 0, n) a[i] = s[i] - 'a';
    F(i, 0, n) b[i] = q[i] - 'a';
    vvl dp(n + 1, vl(n + 1, -1));
    vl freq(26);
    l answer = dfs(a, 0, b, 0, freq, dp);
    if (answer == INF) answer = -1;
    cout << answer << lf;
  }
}

#if defined(RANDOM_TEST)

void solve_brute(istream& cin, ostream& cout) {
  string s, r;
  cin >> s >> r;
  l n = s.size();
  queue<pair<string, l>> q;
  q.emplace(s, 0);
  l answer = -1;
  while (not q.empty()) {
    string a; l w; tie(a, w) = q.front(); q.pop();
    if (w > n) break;
    if (a == r) {
      answer = w;
      break;
    }
    F(i, 0, n) {
      F(j, i + 2, n + 1) {
        string b = a;
        b[i] = a[j - 1];
        F(k, i + 1, j) b[k] = a[k - 1];
        q.emplace(b, w + 1);
      }
    }
  }
  cout << answer << lf;
}

void generate(l size, ostream& cout) {
  string s = rnd.next_string(size, "abcdefghijklmnopqrstuvwxyz");
  string t = s;
  shuffle(all(t), rnd.source);
  cout << s << lf << t << endl;
}

#endif

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  _random_test_size_to = 7;
  _random_test_count = 10000;
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
  return 0;
}
