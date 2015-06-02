#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const int N = 20;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int m[N][N];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> m[i][j];
    }
  }
  const int dx[] = {1, 1, 0, 1};
  const int dy[] = {0, 1, 1, -1};
  ll best = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int d = 0; d < 4; d++) {
        ll v = 1;
        for (int k = 0; k < 4; k++) {
          int x = i + k * dx[d];
          int y = j + k * dy[d];
          if (x < 0 || x >= N || y < 0 || y >= N) {
            v = 0;
            break;
          }
          v *= m[x][y];
        }
        best = max(best, v);
      }
    }
  }
  cout << best << endl;
}
