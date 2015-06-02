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

const int MAX = 3000;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  vi best(MAX + 1, -1);
  for (int c = 1; c < MAX; c++) {
    for (int a = 1; a < c; a++) {
      int b = round(sqrt(c * c - a *a));
      if (b < a) break;
      if (a * a + b * b != c * c || a + b + c > MAX) continue;
      best[a + b + c] = max(best[a + b + c], a * b * c);
    }
  }
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    cout << best[n] << endl;
  }
}
