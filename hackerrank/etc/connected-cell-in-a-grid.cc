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
const l MAX = 10;
int M[MAX][MAX];
l rows, columns;

l flood(l i, l j) {
  l result = 0;
  queue<ll> q;
  q.emplace(i, j);
  M[i][j] = 0;
  result++;
  while (!q.empty()) {
    l x, y;
    tie(x, y) = q.front(); q.pop();
    for (l dx = -1; dx < 2; dx++)
    for (l dy = -1; dy < 2; dy++) {
      l r = x + dx;
      l c = y + dy;
      if (r < 0 || r == rows || c < 0 || c == columns) continue;
      if (M[r][c]) {
        result++;
        M[r][c] = 0;
        q.emplace(r, c);
      }
    }
  }
  return result;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  cin >> rows >> columns;
  for (l r = 0; r < rows; r++) {
    for (l c = 0; c < columns; c++) {
      cin >> M[r][c];
    }
  }
  l answer = 0;
  for (l r = 0; r < rows; r++) {
    for (l c = 0; c < columns; c++) {
      if (M[r][c]) answer = max(answer, flood(r, c));
    }
  }
  cout << answer << endl;
}
