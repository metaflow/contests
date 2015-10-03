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

l gcd(l a, l b) {
  while (b) {
    l t = b;
    b = a % b;
    a = t;
  }
  return a;
}

l lcm(l a, l b) {
  return a * b / gcd(a, b);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    l n2 = n * n;
    priority_queue<l> q, r;
    for (l i = 0; i < n2; i++) {
      l a; cin >> a; q.push(a);
    }
    vl solution;
    for (l i = 0; i < n2; i++) {
      l k = q.top(); q.pop();
      if (!r.empty() && k == r.top()) {
        r.pop();
        continue;
      }
      for (auto j : solution) {
        r.push(gcd(j, k));
        r.push(gcd(j, k));
      }
      solution.push_back(k);
    }
    for (l i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << solution[i];
    }
    cout << endl;
  }
}
