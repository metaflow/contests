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
const int MAX = 1000001;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vi d(MAX);
  for (ll i = 2; i < MAX; i++) {
    for (ll j = i; j < MAX; j += i) d[j]++;
  }
  vi best(MAX);
  best[1] = 1;
  for (ll i = 2; i < MAX; i++) {
    if (d[best[i - 1]] > d[i]) {
      best[i] = best[i - 1];
    } else {
      best[i] = i;
    }
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    cout << best[n] << endl;
  }
}
