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
  ll n, a1, a2, b1, b2, c1, c2;
  while (cin >> n >> a1 >> a2 >> b1 >> b2 >> c1 >> c2) {
    ll m = n - b1 - c1;
    m = min(m, a2);
    cout << m << " ";
    n -= m;
    m = n - c1;
    m = min(m, b2);
    cout << m << " " << (n - m) << endl;
  }
}
