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

const int MAX = 10001;
const int MAX_D = 3020;
int digits[MAX][MAX_D];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  fill(&digits[0][0], &digits[MAX][0], 0);
  // vvi digits(MAX);
  vll sum(MAX);
  for (int i = 0; i < MAX; i++) {
    if (i == 0) {
      digits[i][0] = 1;
      continue;
    }
    for (int j = 0; j < MAX_D; j++) {
      digits[i][j] = digits[i - 1][j] * 2;
    }
    for (int j = 0; j < MAX_D - 1; j++) {
      digits[i][j + 1] += digits[i][j] / 10;
      digits[i][j] %= 10;
    }
    for (int j = 0; j < MAX_D; j++) sum[i] += digits[i][j];
  }
  int tcc; cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    cout << sum[n] << endl;
  }
}
