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

const int MAX = 2000;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n;
  while (cin >> n) {
    vll v(n);
    vll counts(MAX + 1);
    for (ll i = 0; i < n; i++){
      cin >> v[i];
      counts[v[i]]++;
    }
    ll c = 1;
    for (ll i = MAX; i > 0; i--) {
      if (counts[i] == 0) continue;
      ll t = c;
      c += counts[i];
      counts[i] = t;
    }
    for (ll i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << counts[v[i]];
    }
    cout << endl;
  }
}
