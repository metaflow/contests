#include<bits/stdc++.h>
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
  l a, b;
  while (cin >> a >> b) {
    double day = 3600 * 24;
    l t = round((day - a) * day / 2 / abs(a - b) / 60);
    t %= (60 * 12);
    l h = t / 60;
    if (h == 0) h = 12;
    l m = t % 60;
    cout << a << " " << b << " "
         << setw(2) << setfill('0') << h << ":" << setw(2) << m << endl;
  }
}
