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

const int MAX = 100;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n, m;
  while (cin >> n >> m) {
    int f[MAX][MAX];
    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < m; j++) {
        f[i][j] = (s[j] == 'W' ? 1 : -1);
      }
    }
    int _ = 0;
    vi row(MAX, 0);
    for (int i = n - 1; i >= 0; i--) {
      for (int j = m - 1; j >= 0; j--) {
        if (f[i][j] == row[j]) continue;
        _++;
        int d = f[i][j] - row[j];
        for (int k = 0; k <= j; k++) row[k] += d;
      }
    }
    cout << _ << endl;
  }
}
