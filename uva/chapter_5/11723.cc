#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int r, n;
  int tc = 0;
  while (cin >> r >> n, r) {
    tc++;
    int a = r / n;
    if (r % n == 0) a--;
    if (a > 26) {
      printf("Case %d: impossible\n", tc);
    } else {
      printf("Case %d: %d\n", tc, a);
    }
  }
}
