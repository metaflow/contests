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
  l n;
  while (cin >> n) {
    vl a(n);
    for (l i = 0; i < n; i++) cin >> a[i];
    l t = -1;
    l sum = 0;
    while (!a.empty()) {
      vl b;
      for (auto i : a) {
        if (i <= sum) {
          sum++;
        } else {
          b.emplace_back(i);
        }
      }
      reverse(b.begin(), b.end());
      swap(a, b);
      t++;
    }
    cout << t << endl;
  }
}
