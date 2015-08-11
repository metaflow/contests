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

const int MAX = 1000000;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    vll powers(10);
    for (ll i = 0; i < 10; i++) powers[i] = pow(i, n);
    ll answer = 0;
    for (ll i = 2; i < MAX; i++) {
      ll a = i;
      ll sum = 0;
      while (a) {
        sum += powers[a % 10];
        a /= 10;
      }
      if (sum == i) answer += i;
    }
    cout << answer << endl;
  }
}
