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
  ll n;
  cin >> n;
  ll a, b, c, d;
  ll i = 0;
  while (cin >> a >> b >> c >> d) {
    i++;
    a = min(a, b);
    c = min(c, d);
    if (n - a >= c) {
      cout << i << " " << a << " " << (n - a) << endl;
      return 0;
    }
  }
  cout << "-1" << endl;
}
