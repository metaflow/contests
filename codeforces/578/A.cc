#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l a, b;
  while (cin >> a >> b) {
    if (b > a) {
      cout << -1 << endl;
      continue;
    }
    l k = (a / b + 1) / 2;
    double t = (double)(a + b) / 2 / k;
    cout << fixed << setprecision(12) <<  t << endl;
  }
}
