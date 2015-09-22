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

struct op {
  l from, to;
  bool is_value;
  l value, mod;
};
const l MAX = e5 + 1;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m;
  while (cin >> m) {
    vector<op> O(m);
    l pos = 0;
    for (l i = 0; i < m; i++) {
      l t; cin >> t;
      O[i].from = pos;
      O[i].is_value = (t == 1);
      if (O[i].is_value) {
        cin >> O[i].value;
        pos++;
      } else {
        l k;
        cin >> O[i].mod >> k;
        pos += O[i].mod * k;
      }
      O[i].to = pos;
    }
    vl v(MAX);
    for (l i = 0; i < m && O[i].from < MAX; i++) {
      if (O[i].is_value) {
        v[O[i].from] = O[i].value;
        continue;
      }
      for (l j = O[i].from; j < min(MAX, O[i].to); j++) {
        v[j] = v[(j - O[i].from) % O[i].mod];
      }
    }
    cin >> n;
    l j = 0;
    vl answer(n);
    for (l i = 0; i < n; i++) {
      l p; cin >> p; p--;
      while (O[j].to <= p) j++;
      if (O[j].is_value) {
        answer[i] = O[j].value;
      } else {
        answer[i] = v[(p - O[j].from) % O[j].mod];
      }
    }
    bool f = true;
    for (auto i : answer) { if (!f) cout << " "; f = false; cout << i; }
    cout << endl;
  }
}
