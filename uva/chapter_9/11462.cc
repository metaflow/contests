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
  ll n;
  while (cin >> n, n) {
    vi count(100);
    for (ll i = 0; i < n; i++) { int a; cin >> a; count[a]++; }
    bool first = true;
    for (ll i = 1; i < 100; i++) {
      while (count[i]) {
        if (!first) cout << " ";
        first = false;
        cout << i;
        count[i]--;
      }
    }
    cout << endl;
  }
}
