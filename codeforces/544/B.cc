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
  ll n, k;
  while (cin >> n >> k) {
    ll m = (n / 2) * n + (n % 2) * (n + 1) / 2;
    if (k > m) {
      cout << "NO" << endl;
    } else {
      cout << "YES" << endl;
      for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
          if (((i + j) % 2 != 0) || k == 0) {
            cout << 'S';
          } else {
            cout << 'L';
            k--;
          }
        }
        cout << endl;
      }
    }
  }
}
