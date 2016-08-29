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
  while (tcc--) {
    int n;
    cin >> n;
    double d = 0;
    if (n != 1) {
      int t = (n - 2) * (n - 2);
      d = (n * n - t) + pow(2, 0.5) * t;
      d = round(d * 1000) / 1000;
    }
    printf("%.3f\n", d);
    if (tcc) printf("\n");
  }
}
