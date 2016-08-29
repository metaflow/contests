#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int bits(int a) {
  int r = 0;
  while (a) {
    r += a % 2;
    a /= 2;
  }
  return r;
}

int main() {
  int n;
  cin >> n;
  while (n--) {
    int m; cin >> m;
    int b1 = bits(m);
    int b2 = 0;
    while (m != 0) {
      b2 += bits(m % 10);
      m /= 10;
    }
    printf("%d %d\n", b1, b2);
  }
}
