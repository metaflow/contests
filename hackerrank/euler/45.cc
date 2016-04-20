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

using F = function<l(l)>;

F get_function(l a) {
  switch (a) {
    case 3: return [] (l x) { return x * (x + 1) / 2; };
    case 5: return [] (l x) { return x * (3 * x - 1) / 2; };
  }
  return [] (l x) { return x * (2 * x - 1); };
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, a, b;
  while (cin >> n >> a >> b) {
    l i = 1, j = 1;
    auto fi = get_function(a);
    auto fj = get_function(b);
    l vi = fi(i), vj = fj(j);
    while (vj < n) {
      if (vi == vj) {
        cout << vi << endl;
      }
      if (vi >= vj) {
        j++;
        vj = fj(j);
        continue;
      }
      while (vi < vj) {
        i++;
        vi = fi(i);
      }
    }
  }
}
