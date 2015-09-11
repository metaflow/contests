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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

// return gcd(a, b) and set x, y: a * x + b * y = gcd(a, b)
ll extended_euclid(ll a, ll b, ll& x, ll& y) {
  if (b == 0) { x = 1; y = 0; return a; }
  ll d = extended_euclid(b, a % b, x, y);
  ll t = y;
  y = x - (a / b) * y;
  x = t;
  return d;
}

// return b: a * b = 1 (mod n)
ll inverse_mod(ll a, ll n) {
  ll x, y;
  ll d = extended_euclid(a, n, x, y);
  if (d != 1) return 0;
  return (x + (abs(x) / n + 1) * n) % n;
}

const int MAX = 200001;
const ll MOD = 1000000007;
vll f(MAX);
vll fi(MAX);

ll c(ll n, ll k) {
  if (n == k || k == 0) return 1;
  ll r = (f[n] * fi[k]) % MOD;
  r = (r * fi[n - k]) % MOD;
  return r;
}

struct cell {
  ll r, c;
  ll v;
  ll b = 0;
};

// const int MAX_N = 2005;
// ll DP[MAX_N][MAX_N];

// ll dp(vector<cell>& v, ll from, ll to) {
//   auto &r = DP[from][to];
//   if (r != -1) return r;
//   r = c(v[to].r + v[to].c - v[from].r - v[from].c, v[to].r - v[from].r);
//   for (ll i = from + 1; i < to; i++) {
//     if (v[i].r >= v[from].r && v[i].r <= v.[to].r &&
//         v[i].c >= v[from].c && v[i].c <= v.[to].c) {
//       r -= dp(from, i) * dp(i, to);
//     }
//   }
//   while (r < 0) r = (r + MOD) % MOD;
// }

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  f[1] = 1;
  fi[1] = inverse_mod(1, MOD);
  for (ll i = 2; i < MAX; i++) {
    f[i] = (f[i - 1] * i) % MOD;
    fi[i] = inverse_mod(f[i], MOD);
  }
  ll h, w, n;
  while (cin >> h >> w >> n) {
    vector<cell> v(n + 1);
    for (ll i = 0; i < n; i++) {
      cin >> v[i].r >> v[i].c;
    }
    // fill(&DP[0][0], &DP[MAX_N][0], -1);
    v[n].r = 1;
    v[n].c = 1;
    sort(v.begin(), v.end(), [](const cell& a, const cell& b) {
      if (a.r != b.r) return a.r > b.r;
      return a.c > b.c;
    });
    for (ll i = 0; i < n + 1; i++) {
      ll t = c(h - v[i].r + w - v[i].c, w - v[i].c);
      for (ll j = 0; j < i; j++) {
        if (v[j].r >= v[i].r && v[j].c >= v[i].c) {
          t -= c(v[j].r - v[i].r + v[j].c - v[i].c, v[j].c - v[i].c) * v[j].v;
          while (t < 0) t = (t + MOD) % MOD;
        }
      }
      v[i].v = t;
    }
    // for (auto u : v) cerr << u.r << " " << u.c << " " << u.v << endl;
    cout << v[n].v << endl;
  }
}
