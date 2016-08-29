#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n;
    cin >> n;
    int age, j;
    for (int i = 0; i < n; i++) {
      cin >> j;
      if (i == n / 2) age = j;
    }
    printf("Case %d: %d\n", tc, age);
  }
}
