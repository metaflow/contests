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

l at(l n) {
  l m = 9;
  l d = 1;
  while (true) {
    if (n > m * d) {
      n -= m * d;
      m *= 10;
      d++;
      continue;
    }
    l k = (n + d - 1) / d + m / 9 - 1;
    l t = d - (n - 1) % d;
    l a = 0;
    while (t--) {
      a = k % 10;
      k /= 10;
    }
    return a;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    l answer = 1;
    for (l i = 0; i < 7; i++) {
      l a; cin >> a;
      answer *= at(a);
    }
    cout << answer << endl;
  }
}
