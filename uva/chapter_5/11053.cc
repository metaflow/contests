#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

ll a, b, n;

ll f(ll i) {
  i = (i * i) % n;
  return (i * a + b) % n;
}

int main() {
  while (cin >> n, n) {
    cin >> a >> b;
    ll r = 0;
    ll t = 0;
    while (true) {
      r = f(r);
      t = f(f(t));
      if (t == r) break;
    }
    int length = 1;
    t = f(r);
    while (t != r) { t = f(t); length++; }
    cout << (n - length) << endl;
  }
}
