#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  ll a, l;
  int tc = 0;
  while (cin >> a >> l, a >= 0) {
    tc++;
    ll t = a;
    ll count = 1;
    while (t != 1) {
      if (t % 2 == 0) {
        t /= 2;
      } else {
        t = 3 * t + 1;
        if (t > l) break;
      }
      count++;
    }
    printf("Case %d: A = %lld, limit = %lld, number of terms = %lld\n",
      tc, a, l, count);
  }
}
