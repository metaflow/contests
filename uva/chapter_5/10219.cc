#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

using pll = pair<ll, ll>;

void mult(pll &a, int k) {
  a.first *= k;
  while (a.first >= 1000000) {
    a.first /= 10;
    a.second++;
  }
}

int main() {
  int n, k;
  while (cin >> n >> k) {
    pll a(1, 0); pll b(1, 0);
    if (k < (n - k)) k = n - k;
    for (int i = k + 1; i <= n; i++) mult(a, i);
    for (int i = 1; i <= n - k; i++) mult(b, i);
    a.second -= b.second;
    while (a.first < b.first * 100 && a.second > 0) {
      a.first *= 10;
      a.second--;
    }
    a.first /= b.first;
    while (a.first > 0) {
      a.first /= 10;
      a.second++;
    }
    cout << a.second << endl;
  }
}
