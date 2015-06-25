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
  vll f(51);
  f[0] = 1;
  f[1] = 1;
  for (ll i = 2; i < 51; i++) f[i] = f[i - 1] + f[i - 2];
  ll n, k;
  while (cin >> n >> k) {
    int p = 1;
    vll answer;
    while (p <= n) {
      if (f[n - p] < k) {
        k -= f[n - p];
        answer.emplace_back(p + 1);
        answer.emplace_back(p);
        p += 2;
      } else {
        answer.emplace_back(p);
        p++;
      }
    }
    for (ll i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << answer[i];
    }
    cout << endl;
  }
}
