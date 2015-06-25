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
const ll INF = 1000000000000000000;
const double EPS = 1e-10;

const int MAX = 51;

ll dpt[MAX];

ll factorial(int n) {
  if (n < 2) return 1;
  return n * factorial(n - 1);
}

ll T(int k) {
  ll &r = dpt[k];
  if (r == -1) {
    if (k > 22) return r = INF;
    if (k <= 1) return r = 1;
    r = 0;
    for (int i = 1; i <= k; i++) r += factorial(i - 2) * T(k - i);
  }
  return r;
}

vll solve(ll n, ll k, ll from) {
  vll r;
  if (n == 0) return r;
  int i = 1;
  ll t = factorial(i - 2) * T(n - i);
  while (k > t) {
    k -= t;
    i++;
    t = factorial(i - 2) * T(n - i);
  }
  r.emplace_back(from + i - 1);
  ll v = k / T(n - i);
  vi d;
  vb b(i, true);
  for (int j = from + 1; j < from + i - 1; j++) {
    d.emplace_back(j);
  }
  for (int j = from + 1; j < from + i - 1; j++) {
    ll sh = v / factorial(from + i - 1 - j);
    int u = 0;
    while (sh) {
      if (b[u]) {
        sh--;
      }
      u++;
    }
    u--;
    r.emplace_back(d[u]);
  }
  r.emplace_back(from);
  auto rest = solve(n - i, k % T(n - i), from + i);
  r.insert(r.begin(), rest.begin(), rest.end());
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  fill(&dpt[0], &dpt[MAX], -1);
  ll n, k;
  cin >> n >> k;
  auto v = solve(n, k, 1);
  for (auto i : v) {
    cout << i << " ";
  }
}
