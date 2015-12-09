#include<vector>
#include<iostream>
#include<algorithm>
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
  l n;
  while (cin >> n) {
    vl index(n);
    for (l i = 0; i < n; i++) {
      l a; cin >> a; a--;
      index[a] = i;
    }
    vl q(n);
    q[n - 1] = 1;
    for (l i = n - 2; i >= 0; i--) {
      if (index[i + 1] < index[i]) {
        q[i] = 1;
      } else {
        q[i] = q[i + 1] + 1;
      }
    }
    l m = n;
    for (l i : q) m = min(m, n - i);
    cout << m << endl;
  }
}
