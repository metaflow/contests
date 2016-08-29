#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  ios_base::sync_with_stdio(false);
  int n;
  while (cin >> n, n) {
    int k = 1;
    int t = n;
    while (t) {
      t /= 2;
      k <<= 1;
    }
    if ((n << 1) == k) {
      cout << n << endl;
    } else {
      cout << ((n << 1) & (k - 1)) << endl;
    }
  }
}
