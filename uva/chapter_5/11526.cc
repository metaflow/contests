#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

ll h(int n) {
  ll i = 1;
  ll r = 0;
  while (i <= n) {
    ll a = n / i;
    ll j = n / a;
    r += a * (j - i + 1);
    i = j + 1;
  }
  return r;
}

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n;
    cin >> n;
    cout << h(n) << endl;
  }
}
