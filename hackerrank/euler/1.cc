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
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    ll n; cin >> n; n--;
    ll a = n / 3;
    ll answer = 3 * a * (a + 1) / 2;
    a = n / 5;
    answer += 5 * a * (a + 1) / 2;
    a = n / 15;
    answer -= 15 * a * (a + 1) / 2;
    cout << answer << endl;
  }
}
