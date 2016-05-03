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
  l T; cin >> T;
  for (l tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": ";
    string x, y; cin >> x >> y;
    l n = x.size();
    l best = -1, best_a = 0, best_b = 0;
    string answer_x, answer_y;
    for (l turn = 0; turn <= n * 2; turn++) {
      l expected_sign = 0;
      l pos = (turn - 1) / 2;
      l sign = 0;
      if (turn) expected_sign = 2 * (turn % 2) - 1;
      string a = x;
      string b = y;
      for (l i = 0; i < n; i++) {
        if (i > 0 && sign == 0 && a[i - 1] != b[i - 1]) {
          sign = (a[i - 1] < b[i - 1]) ? -1 : 1;
        }
        if (a[i] != '?' && b[i] != '?') continue;
        bool trial = (pos == i) && (expected_sign != 0);
        if (a[i] == '?' && b[i] == '?') {
          a[i] = b[i] = '0';
          if (sign == 1) { b[i] = '9'; continue; }
          if (sign == -1) { a[i] = '9'; continue; }
          if (!trial) continue;
          if (expected_sign == 1) { a[i] = '1'; } else { b[i] = '1'; }
          continue;
        }
        if (a[i] == '?') {
          if (sign == 1) { a[i] = '0'; continue; }
          if (sign == -1) { a[i] = '9'; continue; }
          a[i] = b[i];
          if (!trial) continue;
          if (expected_sign == 1 && b[i] != '9') a[i] = b[i] + 1;
          if (expected_sign == -1 && b[i] != '0') a[i] = b[i] - 1;
          continue;
        }
        if (sign == 1) { b[i] = '9'; continue; }
        if (sign == -1) { b[i] = '0'; continue; }
        b[i] = a[i];
        if (!trial) continue;
        if (expected_sign == 1 && a[i] != '0') b[i] = a[i] - 1;
        if (expected_sign == -1 && a[i] != '9') b[i] = a[i] + 1;
      }
      auto va = stol(a);
      auto vb = stol(b);
      l d = abs(va - vb);
      bool take = true;
      if (best != -1 && d > best) take = false;
      if (d == best) {
        if (va > best_a) take = false;
        if (va == best_a && vb > best_b) take = false;
      }
      if (!take) continue;
      best = d;
      best_a = va;
      best_b = vb;
      answer_x = a;
      answer_y = b;
    }
    cout << answer_x << " " << answer_y << endl;
  }
}
