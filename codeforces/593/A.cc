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
const l MAX = 26;


int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    l count[MAX][MAX] = {0};
    for (l i = 0; i < n; i++) {
      string s;
      cin >> s;
      char a = ' ';
      char b = ' ';
      for (auto c : s) {
        if (a == ' ' || a == c) {
          a = c;
          continue;
        }
        if (b == ' ' || b == c) {
          b = c;
          continue;
        }
        a = ' ';
        break;
      }
      if (a == ' ') continue;
      l k = s.size();
      if (b == ' ') {
        for (l j = 0; j < MAX; j++) {
          if (j == (a - 'a')) continue;
          count[a - 'a'][j] += k;
          count[j][a - 'a'] += k;
        }
      } else {
        count[a - 'a'][b - 'a'] += k;
        count[b - 'a'][a - 'a'] += k;
      }
    }
    l best = 0;
    for (l i = 0; i < MAX; i++) {
      for (l j = 0; j < MAX; j++) {
        best = max(best, count[i][j]);
      }
    }
    cout << best << endl;
  }
}
