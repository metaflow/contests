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
  while (true) {
    vl values;
    char sign = '+';
    l target, min_value = 0, max_value = 0;
    char question, next_sign;
    while (true) {
      if (! (cin >> question >> next_sign)) return 0;
      if (sign == '+') {
        values.emplace_back(1);
      } else {
        values.emplace_back(-1);
      }
      if (next_sign == '=') {
        cin >> target;
        break;
      }
      swap(sign, next_sign);
    }
    l value = 0;
    for (auto& v : values) {
      if (v > 0) {
        max_value += target;
        min_value += 1;
      } else {
        max_value -= 1;
        min_value -= target;
        v = -target;
      }
    }
    value = min_value;
    if (target < min_value || target > max_value) {
      cout << "Impossible" << endl;
    } else {
      l d = target - value;
      for (auto& i : values) {
        if (i < 0 && i != -1) {
          l t = min(target - 1, d);
          value += t;
          i += t;
          d = target - value;
        } else if (i > 0 && i != target) {
          l t = min(target - 1, d);
          value += t;
          i += t;
          d = target - value;
        }
        if (d == 0) break;
      }
      cout << "Possible" << endl;
      bool first = true;
      for (auto i : values) {
        if (!first) {
          cout << " " << (i > 0 ? '+' : '-') << " ";
        }
        first = false;
        cout << abs(i);
      }
      cout << " = " << target << endl;
    }
  }
}
