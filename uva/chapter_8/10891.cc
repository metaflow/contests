#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

const int MAX = 101;
ll memo[MAX][MAX];
bool known[MAX][MAX];

// best for [a, b]
ll dp(int a, int b, vll& sum) {
  if (a > b) return 0;
  if (!known[a][b]) {
    known[a][b] = true;
    ll &r = memo[a][b];
    r = -INF;
    for (int i = a; i <= b; i++) {
      r = max(r, sum[i + 1] - sum[a] - dp(i + 1, b, sum));
      r = max(r, sum[b + 1] - sum[i] - dp(a, i - 1, sum));
    }
  }
  return memo[a][b];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n;
  while (cin >> n, n) {
    vll sum(n + 1);
    sum[0] = 0;
    for (int i = 0; i < n; i++) {
      int v; cin >> v;
      sum[i + 1] = sum[i] + v;
    }
    fill(&known[0][0], &known[MAX][0], false);
    ll answer = dp(0, n - 1, sum);
    cout << answer << endl;
  }
}
