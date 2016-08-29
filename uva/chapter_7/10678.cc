#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  ios_base::sync_with_stdio(false);
  int tcc;
  cin >> tcc;
  while (tcc--) {
    double d, l;
    cin >> d >> l;
    double a = l / 2;
    double b = sqrt(l * l - d * d) / 2;
    printf("%.3lf\n", M_PI * a * b);
  }
}
