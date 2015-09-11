#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using l = long long;
using lu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vl = vector<l>;
using vvl = vector<vl>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;
const int MAX = 501;
const int RUN = 250;

l S[2][MAX][MAX];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  l n, m, b, mod;
  while (cin >> n >> m >> b >> mod) {
    vl bugs(n);
    for (l i = 0; i < n; i++) cin >> bugs[i];
    fill(&S[0][0][0], &S[2][0][0], 0);
    S[0][0][0] = 1;
    for (l i = 0; i < n; i++) {
      l current = (i + 1) & 1;
      l prev = i & 1;
      for (l j = 0; j <= m; j++) {
        for (l k = 0; k <= b; k++) {
          S[current][j][k] = S[prev][j][k];
          if (j > 0 && k - bugs[i] >= 0) {
            S[current][j][k] += S[current][j - 1][k - bugs[i]];
          }
          S[current][j][k] %= mod;
        }
      }
    }
    l total = 0;
    l last = n & 1;
    for (l i = 0; i <= b; i++) {
      total = (total + S[last][m][i]) % mod;
    }
    cout << total << endl;
  }
}
