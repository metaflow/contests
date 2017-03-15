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

const l MAX = 200;
const l MAX_RED = 40001;
l memo[MAX][MAX_RED][2];

l f(vl& h, l p, l a, l b, l last_a) {
  if (p < 0) return 0;
  l& r = memo[p][a][last_a];
  if (r == -1) {
    r = INF;
    if (h[p] <= a) {
      r = min(r, f(h, p - 1, a - h[p], b, 1) +
              (last_a ? 0 : min(h[p], h[p + 1])));
    }
    if (h[p] <= b) {
      r = min(r, f(h, p - 1, a, b - h[p], 0) +
              (last_a ? min(h[p], h[p + 1]) : 0));
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
#if defined ONLINE_JUDGE
  ifstream fin("input.txt"); cin.rdbuf(fin.rdbuf());
  ofstream fout("output.txt"); cout.rdbuf(fout.rdbuf());
#endif
  l a, b, n;
  while (cin >> n >> a >> b) {
    vl v(n);
    F(i, 0, n) cin >> v[i];
    v.emplace_back(0);
    fill(&memo[0][0][0], &memo[MAX][0][0], -1);
    l answer = f(v, n - 1, a, b, 0);
    if (answer == INF) {
      cout << "-1\n";
    } else {
      cout << answer << '\n';
    }
  }
}
