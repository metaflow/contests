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

void search(l u, vl& left, vl& right, vl& v, l a, l b, unordered_set<l>& found) {
  if (u < 0) return;
  if (v[u] >= a and v[u] <= b) found.emplace(v[u]);
  search(left[u], left, right, v, a, min(b, v[u] - 1), found);
  search(right[u], left, right, v, max(a, v[u] + 1), b, found);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vl parent(n, -1);
    vl left(n), right(n);
    vl v(n);
    F(i, 0, n) {
      cin >> v[i] >> left[i] >> right[i];
      left[i]--; right[i]--;
      if (left[i] > -1) parent[left[i]] = i;
      if (right[i] > -1) parent[right[i]] = i;
    }
    l root = 0;
    while (parent[root] > -1) root = parent[root];
    l a = -1, b = e9 + 1;
    unordered_set<l> found;
    search(root, left, right, v, a, b, found);
    l answer = 0;
    for (const l i : v) if (not found.count(i)) answer++;
    cout << answer << lf;
  }
}
