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
using vvll = vector<vll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  ll n;
  while (cin >> n) {
    set<ll> products;
    vector<int> digits;
    for (int i = 1; i <= n; i++) digits.emplace_back(i);
    while (true) {
      for (int i = 1; i < n; i++) {
        ll a = 0;
        for (int k = 0; k < i; k++) a = a * 10 + digits[k];
        for (int j = i + 1; j < n; j++) {
          ll b = 0;
          for (int k = i; k < j; k++) b = b * 10 + digits[k];
          ll c = 0;
          for (int k = j; k < n; k++) c = c * 10 + digits[k];
          if (c == a * b) products.insert(c);
          if (c < a * b) break;
        }
      }
      if (!next_permutation(digits.begin(), digits.end())) break;
    }
    cout << accumulate(products.begin(), products.end(), 0) << endl;
  }
}
