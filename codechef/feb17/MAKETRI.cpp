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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, L, R;
  while (cin >> n >> L >> R) {
    vl v(n);
    for (l i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    stack<ll> parts;
    for (l i = 0; i < n - 1; i++) {
      ll p(v[i + 1] - v[i] + 1, v[i] + v[i + 1] - 1);
      while (not parts.empty() and parts.top().second >= p.first) {
        p.first = min(p.first, parts.top().first);
        parts.pop();
      }
      parts.push(p);
    }
    l answer = 0;
    while (not parts.empty()) {
      auto p = parts.top(); parts.pop();
      answer += max((l)0, min(R, p.second) - max(L, p.first) + 1);
    }
    cout << answer << '\n';
  }
}
