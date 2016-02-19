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
  l n;
  while (cin >> n) {
    priority_queue<l, vl, greater<l>> q;
    for (l i = 0; i < n; i++) {
      l a; cin >> a; q.emplace(a);
    }
    l k = 0, t = 0;
    while (!q.empty()) {
      l a = q.top(); q.pop();
      if (!q.empty() && q.top() == a) {
        q.pop(); q.push(a + 1);
        continue;
      }
      t += a - k;
      k = a + 1;
    }
    cout << t << endl;
  }
}
