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
  vll f(10);
  f[0] = 1;
  for (ll i = 1; i < 10; i++) f[i] = i * f[i - 1];
  ll n; cin >> n;
  ll answer = 0;
  for (ll i = 10; i < n; i++) {
    ll sum = 0;
    ll t = i;
    while (t) {
      sum += f[t % 10];
      t /= 10;
    }
    if (sum % i == 0) answer += i;
  }
  cout << answer << endl;
}
