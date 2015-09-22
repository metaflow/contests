// time 1:17:00 +
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
const l MAX = 151;

l DP[MAX][MAX][2];
l last_row;
l n, m;

l dp(l row, l col, l right, vl& LB, vl& RB);

l f(l row, l col, l right, vl& LB, vl& RB) {
  // move left
  l k = INF;
  for (l i = 0; i <= col; i++) {
    k = min(k, 1 + col - i + right + dp(row + 1, i, 1, LB, RB));
  }
  // move right
  for (l i = col; i < m; i++) {
    k = min(k, 1 + i - col + (1 - right) + dp(row + 1, i, 0, LB, RB));
  }
  return k;
}

l dp(l row, l col, l right, vl& LB, vl& RB) {
  if (row > last_row) return -1;
  l& d = DP[row][col][right];
  if (d != -1) return d;
  d = INF;
  // if empty
  if (LB[row] == -1) {
    return d = f(row, col, right, LB, RB);
  }
  // to the right and then to the left
  l t = 0;
  l orientation = right;
  l c = col;
  if (RB[row] > c) {
    t += RB[row] - c + (1 - orientation);
    orientation = 1;
    c = RB[row];
  }
  t += orientation;
  t += c - LB[row];
  d = min(d, t + f(row, LB[row], 0, LB, RB));
  // to the left and then to the right
  t = 0;
  orientation = right;
  c = col;
  if (LB[row] < c) {
    t += c - LB[row] + orientation;
    orientation = 0;
    c = LB[row];
  }
  t += 1 - orientation;
  t += RB[row] - c;
  d = min(d, t + f(row, RB[row], 1, LB, RB));
  return d;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);

  while (cin >> n >> m) {
    vl left_bound(n, -1), right_bound(n, -1);
    for (l i = 0; i < n; i++) {
      string s; cin >> s;
      for (l j = 0; j < m; j++) {
        if (s[j] == 'G') continue;
        if (left_bound[i] == -1) left_bound[i] = j;
        right_bound[i] = j;
      }
    }
    last_row = n - 1;
    while (last_row >= 0 && right_bound[last_row] == -1) last_row--;
    if (last_row < 0) {
      cout << 0 << endl;
    } else {
      fill(&DP[0][0][0], &DP[MAX][0][0], -1);
      cout << dp(0, 0, 1, left_bound, right_bound) << endl;
    }
  }
}

