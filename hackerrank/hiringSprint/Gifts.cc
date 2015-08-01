#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

ll n;
vi b, s, g;
vi stones;
const int MAX = 11;

int memo[MAX][MAX][MAX][MAX][MAX][MAX][3 * MAX];

int dp(ll bs, ll be, ll ss, ll se, ll gs, ll ge, ll p) {
  if (p == n) return 0;
  auto &r = memo[bs][be][ss][se][ge][ge][p];
  if (r == 0) {
    int v = stones[p];
    p++;
    if (bs != be) {
      r = max(dp(bs + 1, be, ss, se, gs, ge, p) + b[bs] * v,
              dp(bs, be - 1, ss, se, gs, ge, p) + b[be - 1] * v);
    }
    if (ss != se) {
      r = max(r,
              max(dp(bs, be, ss + 1, se, gs, ge, p) + s[ss] * v,
              dp(bs, be, ss, se - 1, gs, ge, p) + s[se - 1] * v));
    }
    if (gs != ge) {
      r = max(r,
              max(dp(bs, be, ss, se, gs + 1, ge, p) + g[gs] * v,
              dp(bs, be, ss, se, gs, ge - 1, p) + g[ge - 1] * v));
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll B, S, G;
  cin >> B >> S >> G;
  b.resize(B);
  s.resize(S);
  g.resize(G);
  fill(&memo[0][0][0][0][0][0][0], &memo[MAX][0][0][0][0][0][0], 0);
  n = B + S + G;
  stones.resize(n);
  for (ll i = 0; i < B; i++) cin >> b[i];
  for (ll i = 0; i < S; i++) cin >> s[i];
  for (ll i = 0; i < G; i++) cin >> g[i];
  for (ll i = 0; i < n; i++) cin >> stones[i];
  cout << dp(0, B, 0, S, 0, G, 0) << endl;
}

