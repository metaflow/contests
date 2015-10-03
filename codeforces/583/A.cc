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
    vb rows(n);
    vb cols(n);
    vl answer;
    for (l i = 0; i < n * n; i++) {
      l a, b; cin >> a >> b; a--; b--;
      if (rows[a] || cols[b]) continue;
      rows[a] = true;
      cols[b] = true;
      answer.emplace_back(i + 1);
    }
    for (l i = 0; i < answer.size(); i++) {
      if (i) cout << ' ';
      cout << answer[i];
    }
    cout << endl;
  }
}
