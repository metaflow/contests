#include <bits/stdc++.h>
#if defined(LOCAL)
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

#if defined(LOCAL)
const bool enable_log = true;
#else
const bool enable_log = false;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

l popcnt(l value) { return __builtin_popcount(value); }
bool bit_set(l mask, l i) { return mask & (e0 << i); }

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m, k;
  while (cin >> n >> m >> k) {
    if (m == 1) {
      l answer = 0;
      F(i, 0, n) {
        l a, b, ca, cb;
        cin >> a >> ca >> b >> cb;
        answer += min(ca, cb);
      }
      cout << answer << lf;
      continue;
    }
    l worst = 0; // worst case cost
    vl not_taken(m); // mask if i is not taken
    l size_b = m / 2;
    l size_a = m - size_b;
    vl cost(m); // negative cost if we take i
    F(i, 0, n) {
      l a, b, ca, cb;
      cin >> a >> ca >> b >> cb; a--; b--;
      not_taken[a] = not_taken[a] | (e0 << b);
      not_taken[b] = not_taken[b] | (e0 << a);
      l c = max(ca, cb);
      worst += c;
      cost[a] += c - ca;
      cost[b] += c - cb;
    }
    vvl cost_b(size_b + 1, vl(e0 << size_b, -1));
    F(i, 0, e0 << size_b) {
      l s = popcnt(i), mask = 0, c = 0;
      if (s > k) continue;
      F(j, 0, size_b) {
        if (i & (e0 << j)) {
          c += cost[j + size_a];
        } else {
          mask = mask | not_taken[j + size_a];
        }
      }
      mask = mask >> size_a;
      if ((mask | i) != i) continue;
      cost_b[s][i] = c;
    }
    F(i, 0, size_b + 1) for (l j = (e0 << size_b) - 1; j >= 0; j--) {
      if (cost_b[i][j] == -1) continue;
      if (i < size_b) cost_b[i + 1][j] = max(cost_b[i + 1][j], cost_b[i][j]);
      F(b, 0, size_b) {
        if (j & (e0 << b)) {
          cost_b[i][j - (e0 << b)] = max(cost_b[i][j - (e0 << b)], cost_b[i][j]);
        }
      }
    }
    l answer = -1;
    F(i, 0, e0 << size_a) {
      l s = popcnt(i), mask = 0, c = 0;
      if (s > k) continue;
      F(j, 0, size_a) {
        if (i & (e0 << j)) {
          c += cost[j];
        } else {
          mask = mask | not_taken[j];
        }
      }
      l t = mask & ((e0 << size_a) - 1);
      if ((t | i) != i) continue;
      l b = min(k - s, size_b);
      l cb = cost_b[b][mask >> size_a];
      if (cb == -1) continue;
      l x = worst - c - cb;
      if (answer == -1 or answer > x) answer = x;
    }
    cout << answer << lf;
  }
}
