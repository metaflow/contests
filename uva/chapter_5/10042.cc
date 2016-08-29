#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int f(int a) {
  int t = 0;
  while (a) {
    t += (a % 10);
    a /= 10;
  }
  return t;
}

int main() {
  bitset<32000> b;
  b.reset();
  vector<int> primes;
  for (int i = 2; i < 32000; i++) {
    if (b[i]) continue;
    primes.emplace_back(i);
    for (ll j = i * i; j < 32000; j += i) b[j] = true;
  }

  int tcc;
  cin >> tcc;
  while (tcc--) {
    int n;
    cin >> n;
    n++;
    while (true) {
      int t = n;
      int sum = 0;
      auto p = primes.cbegin();
      while (p != primes.cend() && ((*p)*(*p) <= t)) {
        while (t % *p == 0) {
          sum += f(*p);
          t /= *p;
        }
        p++;
      }
      if (t != 1) {
        sum += f(t);
        if (t == n) sum = 0;
      }
      if (f(n) == sum) {
        cout << n << endl;
        break;
      }
      n++;
    }
  }
}
