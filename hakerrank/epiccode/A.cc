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
  ll n, p, x;
  ll m = -1;
  ll m_i = 0;
  cin >> n >> p >> x;
  for (ll i = 0; i < n; i++) {
    ll a; cin >> a;
    if (a * p > m) {
      m_i = i;
      m = a * p;
    }
    p -= x;
  }
  cout << m_i + 1 << endl;
}
