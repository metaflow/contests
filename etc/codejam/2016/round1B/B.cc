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
  l tcc; cin >> tcc;
  for (l tc = 1; tc <= tcc; tc++) {
    cout << "Case #" << tc << ": ";
    string a, b; cin >> a >> b;
    l ma = -1, mb = -1;
    l n = a.size();
    for (l i = 0; i < n; i++) if (a[i] != '?') { ma = i - 1; break; }
    for (l i = 0; i < n; i++) if (b[i] != '?') { mb = i - 1; break; }
    ma = min(ma, mb);
    l best_a = 0, best_b = 0;
    string best_as, best_bs;
    for (l t = 0; t < 5; t++) {
      auto ta = a;
      auto tb = b;
      for (l i = 0; i <= ma; i++) ta[i] = tb[i] = '0';
      if (ma > -1) {
        if (t == 1) ta[ma] = '1';
        if (t == 2) tb[ma] = '1';
      }
      l sign = 0;
      for (l i = 0; i < n; i++) {
        if (ta[i] == '?' && tb[i] == '?') {
          if (sign < 0) {
            ta[i] = '9';
            tb[i] = '0';
          } else if (sign > 0) {
            ta[i] = '0';
            tb[i] = '9';
          } else {
            ta[i] = tb[i] = '0';
          }
        } else if (ta[i] == '?') {
          if (sign < 0) {
            ta[i] = '9';
          } else if (sign > 0) {
            ta[i] = '0';
          } else {
            ta[i] = tb[i];
            if ((t == 1 || t == 3) && tb[i] != '9') ta[i] = tb[i] + 1;
            if ((t == 2 || t == 4) && tb[i] != '0') ta[i] = tb[i] - 1;
          }
        } else if (tb[i] == '?') {
          if (sign < 0) {
            tb[i] = '0';
          } else if (sign > 0) {
            tb[i] = '9';
          } else {
            tb[i] = ta[i];
            if ((t == 1 || t == 3) && ta[i] != '0') tb[i] = ta[i] - 1;
            if ((t == 2 || t == 4) && ta[i] != '9') tb[i] = ta[i] + 1;
          }
        }
        if (sign != 0 || ta[i] == tb[i]) continue;
        if (ta[i] < tb[i]) {
          sign = -1;
        } else {
          sign = 1;
        }
      }
      l x = stol(ta);
      l y = stol(tb);
      bool eq = abs(x - y) == abs(best_a - best_b);
      if (t == 0 ||
          (abs(x - y) < abs(best_a - best_b)) ||
          (eq && (best_a > x)) ||
          (eq && (best_a == x && best_b > y))) {
        best_as = ta;
        best_bs = tb;
        best_a = x;
        best_b = y;
      }
    }
    cout << best_as << ' ' << best_bs << endl;
  }
}
