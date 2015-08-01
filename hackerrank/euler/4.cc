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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc;
  cin >> tcc;
  vi palindromes;
  for (int i = 100; i < 1000; i++) {
    for (int j = i; j < 1000; j++) {
      int m = i * j;
      int t = 100000;
      if (m < t) continue;
      if (m / t != m % 10) continue;
      m /= 10; t /= 100;
      if ((m / t) % 10 != m % 10) continue;
      m /= 10; t /= 100;
      if ((m / t) % 10 != m % 10) continue;
      palindromes.emplace_back(i * j);
    }
  }
  sort(palindromes.begin(), palindromes.end());
  // for (auto p : palindromes) cout << p << endl;
  for (int tc = 1; tc <= tcc; tc++) {
    int n; cin >> n;
    auto p = lower_bound(palindromes.begin(), palindromes.end(), n);
    p--;
    ll answer = *p;
    cout << answer << endl;
  }
}
