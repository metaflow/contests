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

l remove_one(priority_queue<ll>& q) {
  l c, v;
  tie(c, v) = q.top(); q.pop();
  c--;
  if (c) q.emplace(c, v);
  return v;
}

char letter(l v) { return 'A' + v; }

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l tcc; cin >> tcc;
  for (l tc = 1; tc <= tcc; tc++) {
    cout << "Case #" << tc << ": ";
    l n; cin >> n;
    l total = 0;
    priority_queue<ll> q;
    for (l i = 0; i < n; i++) {
      l x; cin >> x;
      q.emplace(x, i);
      total += x;
    }
    bool first = true;
    while (total > 0) {
      if (!first) cout << " ";
      first = false;
      if (total == 3) {
        cout << letter(remove_one(q));
        total--;
        continue;
      }
      cout << letter(remove_one(q)) << letter(remove_one(q));
      total -= 2;
    }
    cout << endl;
  }
}
