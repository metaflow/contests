#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l,l>; using vll = vector<ll>; using vvll = vector<vll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l a, b, c, x, y, z;
  while (cin >> a >> b >> c >> x >> y >> z) {
    l need = max(x - a, (l)0) + max(y - b, (l)0) + max(z - c, (l)0);
    l left = max(a - x, (l)0) / 2 + max(b - y, (l)0) / 2 + max(c - z, (l)0) / 2;
    if (need <= left) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
}
