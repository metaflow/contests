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

l size = 100;
l sh = size / 2;

void try_point(l x, l y, queue<ll>& q, vvb& m) {
  l i = x + sh, j = y + sh;
  if (i < 0 || i >= size || j < 0 || j >= size) return;
  if (m[i][j]) return;
  m[i][j] = true;
  q.emplace(x, y);
}

vvb get_map(l a, l b) {
  vvb m(size, vb(size));
  queue<ll> q;
  try_point(a, b, q, m);
  while (!q.empty()) {
    l i, j;
    tie(i, j) = q.front(); q.pop();
    try_point(i + j, j, q, m);
    try_point(i - j, j, q, m);
    try_point(i, i + j, q, m);
    try_point(i, i - j, q, m);
  }
  return m;
}

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

bool reachable(l a, l b, l x, l y) {
  return gcd(a, b) == gcd(x, y);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  /*
  for (l a = 1; a < 30; a++) {
    for (l b = 1; b < 30; b++) {
      auto m = get_map(a, b);
      for (l x = 1; x < 30; x++) {
        for (l y = 1; y < 30; y++) {
          if (m[x + sh][y + sh] != reachable(a, b, x, y)) {
            cout << a << ", " << b << " " << x << ", " << y << endl;
            return 0;
          }
        }
      }
    }
  }*/
  l tcc; cin >> tcc;
  for (l tc = 0; tc < tcc; tc++) {
    l a, b, x, y;
    cin >> a >> b >> x >> y;
    cout << (reachable(a, b, x, y) ? "YES" : "NO") << endl;
  }
}
