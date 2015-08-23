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
const int MAX = 5001;

ll dp[MAX][MAX];
ll group_size;

ll pick(int left, int big, vll& acc, ll from) {
  ll &r = dp[left][big];
  if (r == -1) {
    if (left == 0) {
      r = 0;
      return r;
    }
    r = INF;
    // pick small
    if (left > big) {
      r = min(r, acc[from + group_size - 1] - acc[from]
          + pick(left - 1, big, acc, from + group_size));
    }
    // pick small + 1
    if (big) {
      r = min(r, acc[from + group_size - 1 + 1] - acc[from]
          + pick(left - 1, big - 1, acc, from + group_size + 1));
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n, k;
  while (cin >> n >> k) {
    vll v(n);
    for (ll i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    vll acc(n + 1);
    for (ll i = 1; i < n; i++) acc[i] = acc[i - 1] + v[i] - v[i - 1];
    fill(&dp[0][0], &dp[MAX][0], -1);
    group_size = n / k;
    ll big = n - group_size * k;
    cout << pick(k, big, acc, 0) << endl;
  }
}
