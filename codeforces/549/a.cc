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

const int MAX = 50;
int f[MAX][MAX];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int m, n;
  while (cin >> n >> m) {
    fill(&f[0][0], &f[MAX][0], 0);
    for (int i = 0; i < n; i++) {
      string s; cin >> s;
      for (int j = 0; j < m; j++) {
        switch (s[j]) {
          case 'f': f[i][j] = 1; break;
          case 'a': f[i][j] = 2; break;
          case 'c': f[i][j] = 4; break;
          case 'e': f[i][j] = 8; break;
        }
      }
    }
    int _ = 0;
    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < m - 1; j++) {
        if ((f[i][j] | f[i + 1][j] | f[i][j + 1] | f[i + 1][j + 1]) == 15) _++;
      }
    }
    cout << _ << endl;
  }
}
