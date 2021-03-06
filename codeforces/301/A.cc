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

l sum(vl& a) {
  return accumulate(a.begin(), a.end(), 0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    l sum = 0, min_abs = INF, negatives = 0;
    for (l i = 0; i < 2 * n - 1; i++) {
      l x; cin >> x;
      if (x < 0) negatives++;
      x = abs(x);
      min_abs = min(min_abs, x);
      sum += x;
    }
    if (n % 2 == 0 && negatives % 2 == 1) sum -= 2 * min_abs;
    cout << sum << endl;
  }
}
