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
  l n; cin >> n;
  const l divisors[] = {2, 3, 5, 7, 11, 13, 17};
  vl d(n + 1);
  for (l i = 0; i < n + 1; i++) d[i] = i;
  l sum = 0;
  while (true) {
    bool ok = true;
    for (l i = 0; i < n - 2; i++) {
      l t = d[i + 1] * 100 + d[i + 2] * 10 + d[i + 3];
      ok = ok && (t % divisors[i] == 0);
    }
    if (ok) {
      l t = 0;
      for (l i = 0; i < n + 1; i++) t = t * 10 + d[i];
      sum += t;
    }
    if (!next_permutation(d.begin(), d.end())) break;
  }
  cout << sum << endl;
}
