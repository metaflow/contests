#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int gcd(int a, int b) {
  if (a == 0) return b;
  return gcd(b % a, a);
}

int main() {
  int n;
  while (cin >> n, n) {
    int a = 0;
    int m;
    while (cin >> m, m) a = gcd(a, abs(n - m));
    cout << a << endl;
  }
}
