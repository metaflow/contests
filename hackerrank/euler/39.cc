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
const l MAX = 5 * e6;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vl count(MAX + 1);
  for (l i = 0; i < 15 * e5; i++) {
    for (l j = i; j < 2 * e6; j++) {
      l k = i * i + j * j;
      l t = round(pow(k, 0.5));
      if (t + i + j > MAX) break;
      if (t * t == k) {
        count[t + i + j]++;
      }
    }
  }
  vl answer(MAX + 1);
  for (l i = 1; i < MAX + 1; i++) {
    answer[i] = answer[i - 1];
    if (count[answer[i]] > count[i]) answer[i] = i;
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    l n; cin >> n;
    cout << answer[n] << endl;
  }
}
