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
const l e0 = 1, e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

// #define ONLINE_JUDGE
#if defined ONLINE_JUDGE
const bool enable_log = false;
#else
const bool enable_log = true;
#endif
struct VoidStream { void operator&(std::ostream&) { } };
#define LOG !(enable_log) ? (void) 0 : VoidStream() & cerr

const l MAX = 19;
bool M[MAX][MAX];
l DP[MAX][e0 << MAX]; // number of Hamiltonian paths
l n, from;
// TODO
l popcnt(l value) { return __builtin_popcount(value); }
bool bit_set(l mask, l i) { return mask & (e0 << i); }

l hamiltonian_paths(l to, l mask) {
  if (to == from) return (mask == (e0 << from)) ? 1 : 0;
  l& r = DP[to][mask];
  if (r == -1) {
    r = 0;
    for (l i = from; i < n; i++) {
      if (bit_set(mask, i) and M[i][to])
        r += hamiltonian_paths(i, mask ^ (e0 << to));
    }
  }
  return r;
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  while (cin >> n) {
    fill(&M[0][0], &M[MAX][0], false);
    fill(&DP[0][0], &DP[MAX][0], -1);
    l m; cin >> m;
    for (l i = 0; i < m; i++) {
      l x, y; cin >> x >> y; x--; y--;
      M[x][y] = M[y][x] = true;
    }
    l total = 0;
    // compiler explorer
    for (l mask = 0; mask < (e0 << n); mask++) {
      if (popcnt(mask) < 3) continue;
      from = -1;
      for (l i = 0; i < n; i++) {
        if (not bit_set(mask, i)) continue;
        if (from == -1) { from = i; continue; }
        if (M[from][i]) total += hamiltonian_paths(i, mask);
      }
    }
    cout << (total / 2) << '\n';
  }
}
