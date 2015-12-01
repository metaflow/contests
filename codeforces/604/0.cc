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
  l xs[] = {500, 1000, 1500, 2000, 2500};
  vl ms(5);
  while (cin >> ms[0]) {
    for (int i = 1; i < 5; i++) cin >> ms[i];
    l total = 0;
    for (int i = 0; i < 5; i++) {
      l w;
      cin >> w;
      total += max(3 * xs[i] / 10,
          ((250 - ms[i]) * xs[i] - 50 * 250 * w) / 250);
    }
    int a, b; cin >> a >> b;
    total += a * 100 - b * 50;
    cout << total << endl;
  }
}
