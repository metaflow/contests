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
  ll n, k;
  cin >> n >> k;
  vll boys(n), girls(n);
  for (ll i = 0; i < n; i++) cin >> boys[i];
  for (ll i = 0; i < n; i++) cin >> girls[i];
  sort(boys.begin(), boys.end());
  sort(girls.begin(), girls.end());
  auto b = boys.begin();
  auto g = girls.begin();
  ll pairs = 0;
  while (g != girls.end()) {
    while (b != boys.end() && (*g - *b) > k) b++;
    if (b == boys.end()) break;
    if (abs(*g - *b) <= k) {
      pairs++;
      b++;
    }
    g++;
  }
  cout << pairs << endl;
}
