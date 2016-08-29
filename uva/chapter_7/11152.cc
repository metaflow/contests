#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int a, b, c;
  while (cin >> a >> b >> c) {
    double p = 0.5 * (a + b + c);
    double s = sqrt(p * (p - a) * (p - b) * (p - c));
    double r_in = s / p;
    double s_in = M_PI * pow(r_in, 2);
    double r_out = (double)a * b * c / 4 / s;
    double s_out = M_PI * pow(r_out, 2);
    s_out -= s;
    s -= s_in;
    printf("%.4f %.4f %.4f\n", s_out, s, s_in);
  }
}
