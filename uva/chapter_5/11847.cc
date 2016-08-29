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
    n++;
    int k = 1;
    while ((1 << k) < n) k++;
    cout << (k - 1) << endl;
  }
}
