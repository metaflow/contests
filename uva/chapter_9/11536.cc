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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n, m, k;
    cin >> n >> m >> k;
    vll v(n);
    for (ll i = 0; i < n; i++) {
      if (i < 3) {
        v[i] = i + 1;
        continue;
      }
      v[i] = (v[i - 1] + v[i - 2] + v[i - 3]) % m + 1;
    }
    vll freq(k, 0);
    ll left = k;
    ll best = INF;
    ll start = 0;
    for (ll i = 0; i < n; i++) {
      ll a = v[i] - 1;
      if (a >= k) continue;
      if (freq[a] == 0) left--;
      freq[a]++;
      if (left) continue;
      while (true) {
        ll b = v[start] - 1;
        if (b >= k) {
          start++;
          continue;
        }
        if (freq[b] == 1) break;
        freq[b]--;
        start++;
      }
      best = min(best, i - start + 1);
    }
    cout << "Case " << tc << ": ";
    if (best == INF) {
      cout << "sequence nai" << endl;
    } else {
      cout << best << endl;
    }
  }
}
