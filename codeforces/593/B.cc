#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>; using vvi = vector<vi>;
using ii = pair<int,int>; using vii = vector<ii>;
using l = long long; using vl = vector<l>; using vvl = vector<vl>;
using ll = pair<l, l>; using vll = vector<ll>;
using lu = unsigned long long;
using vb = vector<bool>; using vvb = vector<vb>;
using vd = vector<double>; using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const l e5 = 100000, e6 = 1000000, e7 = 10000000, e9 = 1000000000;

bool intersects(vl& k, vl& b, l x1, l x2) {
  l n = k.size();
  vll y1(n), y2(n), pos1(n), pos2(n);
  for (l i = 0; i < n; i++) {
    y1[i] = {k[i] * x1 + b[i], i};
    y2[i] = {k[i] * x2 + b[i], i};
  }
  sort(y1.begin(), y1.end());
  sort(y2.begin(), y2.end());
  for (l i = 0; i < n; i++) {
    pos1[y1[i].second] = {i, i};
    pos2[y2[i].second] = {i, i};
  }
  for (l i = 1; i < n; i++) {
    if (y1[i].first == y1[i - 1].first)
      pos1[y1[i].second].first = pos1[y1[i - 1].second].first;
    if (y2[i].first == y2[i - 1].first)
      pos2[y2[i].second].first = pos2[y2[i - 1].second].first;
  }
  for (l i = n - 2; i >= 0; i--) {
    if (y1[i].first == y1[i + 1].first)
      pos1[y1[i].second].second = pos1[y1[i + 1].second].second;
    if (y2[i].first == y2[i + 1].first)
      pos2[y2[i].second].second = pos2[y2[i + 1].second].second;
  }
  for (l i = 0; i < n; i++) {
    if ((pos1[i].second < pos2[i].first) || (pos2[i].second < pos1[i].first))
      return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n;
  while (cin >> n) {
    vl k(n), b(n);
    l x1, x2;
    cin >> x1 >> x2;
    for (l i = 0; i < n; i++) {
      cin >> k[i] >> b[i];
    }
    if (intersects(k, b, x1, x2)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
}
