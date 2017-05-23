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

l popcnt(l value) { return __builtin_popcount(value); }
bool bit_set(l mask, l i) { return mask & (e0 << i); }

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  // solution
  l n, from;
  while (cin >> n) {
    fill(&M[0][0], &M[MAX][0], false);
    fill(&DP[0][0], &DP[MAX][0], 0);
    l m; cin >> m;
    for (l i = 0; i < m; i++) {
      l x, y; cin >> x >> y; x--; y--;
      M[x][y] = M[y][x] = true;
    }
    for (l i = 0; i < n; i++) DP[i][e0 << i] = 1;
    l total = 0;
    for (l mask = 1; mask < (e0 << n); mask++) {
      from = -1;
      for (l i = 0; i < n; i++) if (mask & (e0 << i)) { from = i; break; }
      for (l i = 0; i < n; i++) {
        if (DP[i][mask] == 0) continue;
        if ((popcnt(mask) > 2) and M[from][i]) total += DP[i][mask];
        for (l j = from + 1; j < n; j++) {
          if (M[i][j] and ((mask | (e0 << j)) != mask))
            DP[j][mask | (e0 << j)] += DP[i][mask];
        }
      }
    }
    cout << (total / 2) << '\n';
  }
}
