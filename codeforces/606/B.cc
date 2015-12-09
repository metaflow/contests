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
  l x, y, x0, y0;
  while (cin >> x >> y >> x0 >> y0) {
    vvb f(x + 1, vb(y + 1, false));
    string s;
    cin >> s;
    l n = s.size();
    vl answer(n);
    l t = x * y;
    for (l i = 0; i < n; i++) {
      if (!f[x0][y0]) {
        answer[i] = 1;
        t--;
      }
      f[x0][y0] = true;
      switch (s[i]) {
        case 'L': y0 = max(y0 - 1, (l)1); break;
        case 'R': y0 = min(y, y0 + 1); break;
        case 'U': x0 = max((l)1, x0 - 1); break;
        case 'D': x0 = min(x, x0 + 1); break;
      }
    }
    for (auto i : answer) {
      cout << i << " ";
    }
    cout << t << endl;
  }
}
