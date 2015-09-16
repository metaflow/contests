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
  string s;
  while (cin >> s) {
    l n = s.size();
    vl v(n);
    for (l i = 0; i < n; i++) v[i] = i;
    l best = INF;
    vl bestv;
    while (true) {
      l t = 0;
      for (l i = 1; i < n; i++) {
        if (s[v[i - 1]] == s[v[i]]) {
          t = INF;
          break;
        }
        if (v[i] < v[i - 1]) t++;
      };
      if (best > t) {
        bestv = v;
        best = t;
      }
      if (!next_permutation(v.begin(), v.end())) break;
    }
    cout << best << endl;
    cout << bestv[0];
    for (l i = 1; i < n; i++) cout << " " << bestv[i];
    cout << endl;
  }
}
