#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  ll n;
  while (cin >> n, n >= 0) {
    n = (n + 1) * n / 2 + 1;
    cout << n << endl;
  }
}
