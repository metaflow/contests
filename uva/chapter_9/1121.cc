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
  ll n, s;
  while (cin >> n >> s) {
    vll v(n);
    for (ll i = 0; i < n; i++) cin >> v[i];
    ll answer = INF;
    ll sum = 0;
    ll j = 0;
    for (ll i = 0; i < n; i++) {
      sum += v[i];
      while (sum >= s) {
        answer = min(answer, i - j + 1);
        sum -= v[j];
        j++;
      }
    }
    if (answer == INF) answer = 0;
    cout << answer << endl;
  }
}
