#include<bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int f(int n) {
  if (n >= 101) return n - 10;
  return 91;
}

int main() {
  int n;
  while (cin >> n, n) {
    printf("f91(%d) = %d\n", n, f(n));
  }
}
