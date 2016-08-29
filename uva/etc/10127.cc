#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  while (cin >> n) {
    int x = 0;
    int m = 0;
    while (true) {
      x++;
      m = (m * 10 + 1) % n;
      if (m == 0) break;
    }
    cout << x << endl;
  }
}
