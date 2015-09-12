// time: 15:00
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
  ll n, m;
  while (cin >> n >> m) {
    if (m < n - 1 || m > (n + 1) * 2) {
      cout << -1 << endl;
      continue;
    }
    if (m > n * 2) {
      cout << "11";
      m -= 2;
    }
    while (m > 0 || n > 0) {
      if (n > 0) {
        cout << "0";
        n--;
      }
      if (m == 0) continue;
      if (m > n && m > 1) {
        cout << "11";
        m -= 2;
      } else {
        cout << "1";
        m--;
      }
    }
    cout << endl;
  }
}
