#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  while (cin >> n, n) {
    n = 1 << (((n - 1960) / 10) + 2);
    int i = 0;
    double a = 0;
    while (a < n) {
      i++;
      a += log2(i);
    }
    a -= log2(i);
    i--;
    cout << i << endl;
  }
}
