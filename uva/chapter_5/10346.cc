#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n, k;
  while (cin >> n >> k) {
    int t = 0;
    int b = 0;
    while (n > 0) {
      t += n;
      b += n;
      n = b / k;
      b = b % k;
    }
    cout << t << endl;
  }
}
