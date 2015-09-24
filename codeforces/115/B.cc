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
  l n, m;
  while (cin >> n >> m) {
    vl L(n + 1, m); // leftmost
    vl R(n + 1, 0); // rightmost
    for (l i = 0; i < n; i++) {
      string s;
      cin >> s;
      for (l j = 0; j < m; j++) {
        if (s[j] == 'G') continue;
        L[i] = min(L[i], j);
        R[i] = max(R[i], j);
      }
    }
    l k = n; // number of non empty
    while (k > 0 && L[k - 1] == m) k--;
    if (k) {
      l answer = k - 1;
      l p = 0;
      for (l i = 0; i < k; i++) {
        if (i % 2 == 0) {
          // ->
          l a = max(R[i], R[i + 1]);
          if (a > p) {
            answer += a - p;
            p = a;
          }
        } else {
          // <-
          l a = min(L[i], L[i + 1]);
          if (a < p) {
            answer += p - a;
            p = a;
          }
        }
      }
      cout << answer << endl;
    } else {
      cout << 0 << endl;
    }
  }
}
