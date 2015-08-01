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

const int MAX = 501;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc; cin >> tcc;
  int r[MAX][MAX];
  for (int i = 0; i < MAX; i++) {
    r[0][i] = 1;
    r[i][0] = 1;
  }
  for (int i = 1; i < MAX; i++) {
    for (int j = 1; j < MAX; j++) {
      r[i][j] = (r[i - 1][j] + r[i][j - 1]) % 1000000007;
    }
  }
  for (int tc = 1; tc <= tcc; tc++) {
    int n, m; cin >> n >> m;
    cout << r[n][m] << endl;
  }
}
