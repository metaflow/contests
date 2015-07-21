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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n, d; cin >> n >> d;
    vll v(n);
    for (ll i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    ll i = v.size() - 1;
    ll answer = 0;
    while (i > 0) {
      if (v[i] - v[i - 1] < d) {
        answer += v[i] + v[i - 1];
        i--;
      }
      i--;
    }
    cout << answer << endl;
  }
}
