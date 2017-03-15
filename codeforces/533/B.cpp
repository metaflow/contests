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

void dfs(l at, vvl& adj, vl& v, vvl& s) {
  for (l i : adj[at]) dfs(i, adj, v, s);
  // pick this: maintain oddity of children.
  l oddity = 0;
  l sum = 0;
  l d = INF;
  for (l i : adj[at]) {
    if (s[i][1] > s[i][0]) {
      oddity++;
      sum += s[i][1];
      d = min(d, s[i][1] - s[i][0]);
    } else {
      sum += s[i][0];
      d = min(d, s[i][0] - s[i][1]);
    }
  }
  l j = oddity % 2;
  s[at][j] = sum;
  s[at][1 - j] = sum - d;
  s[at][1] = max(s[at][1], s[at][0] + v[at]);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vvl adj(n); vl v(n);
    F(i, 0, n) {
      l p; cin >> p >> v[i]; p--;
      if (p >= 0) adj[p].emplace_back(i);
    }
    vvl s(n, vl(2, 0)); // [i][0] - sum with even #, [i][1] - odd
    dfs(0, adj, v, s);
    cout << max(s[0][0], s[0][1]) << '\n';
  }
}
