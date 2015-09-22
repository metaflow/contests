//time 0:17:40
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
    vl one, two;
    for (l i = 0; i < n; i++) {
      l t, w;
      cin >> t >> w;
      if (t == 1) {
        one.emplace_back(w);
      } else {
        two.emplace_back(w);
      }
    }
    sort(one.begin(), one.end());
    vl w1(one.size() + 1);
    for (l i = 0; i < one.size(); i++) w1[i + 1] = w1[i] + one[i];

    sort(two.begin(), two.end());
    vl w2(two.size() + 1);
    for (l i = 0; i < two.size(); i++) w2[i + 1] = w2[i] + two[i];

    l best = INF;
    for (l i = 0; i <= one.size(); i++) {
      for (l j = 0; j <= two.size(); j++) {
        l w = one.size() - i + (two.size() - j) * 2;
        if (w1[i] + w2[j] > w) break;
        best = min(best, w);
      }
    }
    cout << best << endl;
  }
}
