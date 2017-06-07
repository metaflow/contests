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

void solve(istream& cin, ostream& cout) {
  string s, q;
  while (cin >> s >> q) {
    l n = s.size();
    vl freq(26);
    for (auto c : s) freq[c - 'a']++;
    for (auto c : q) freq[c - 'a']--;
    bool ok = true;
    for (auto i : freq) ok = ok and i == 0;
    if (not ok) {
      cout << -1 << lf;
      continue;
    }
    l i = 0, j = 0;
    l answer = 0;
    while (j < n) {
      if (s[i] == q[j]) {
        i++;
        j++;
        continue;
      }
      if (freq[s[i] - 'a']) {
        i++;
        freq[s[i] - 'a']--;
      } else {
        freq[q[j] - 'a']++;
        j++;
        answer++;
      }
    }
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
  while (1) {
    string a; l w; tie(a, w) = q.front(); q.pop();
    if (w > n) break;
    if (a == r) {
      answer = w;
      break;
    }
    F(i, 0, n) {
      F(j, i + 2, n) {
        string b = a;
        b[i] = a[j - 1];
        F(k, i + 1, j) b[i] = a[i - 1];
        q.emplace(b, w + 1);
      }
    }
  }
  cout << answer << lf;
}

void generate(l size, ostream& cout) {
  string s = rnd.next_string(size);
  string t = s;
  shuffle(all(t), rnd.source);
  cout << s << lf << t << endl;
}

#endif

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cout << fixed << setprecision(15);
#if defined(LOCAL)
  maybe_run_tests(cin, cout);
#else
  solve(cin, cout);
#endif
}
