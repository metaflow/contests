#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  double x, y, s;
  while (cin >> x >> y >> s) {
    double t = x + y;
    double p = x / t * y / (t - s - 1) + y / t * (y - 1) / (t - s - 1);
    printf("%.5f\n", p);
  }
}
