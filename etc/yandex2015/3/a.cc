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
  int h, l, h1, h2, l1, l2;
  while (cin >> h >> l >> h1 >> h2 >> l1 >> l2) {
    double a = atan2(h, l) * 2;
    double m = (a * (h1 + h2) + (M_PI - a) * (l1 + l2)) / 2 / M_PI;
    cout << setprecision(8) << m << endl;
  }
}
