#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

ll get_line(ll n) {
  ll a = floor(pow(n, 0.5));
  if ((a + 1) * (a + 1) < n) ++a;
  return a;
}

double get_x(ll n) {
  ll a = get_line(n);
  return (n - a * a - a) * 0.5;
}

double get_y(int n) {
  ll a = get_line(n);
  double h = pow(3, 0.5) / 2;
  double y = a * h;
  if ((n + a) % 2 == 1) y -= h/3;
  return y;
}

int main() {
  ll m, n;
  while (cin >> m >> n) {
    double xm = get_x(m);
    double xn = get_x(n);
    double ym = get_y(m);
    double yn = get_y(n);
    double r = pow(pow(xm - xn, 2) + pow(yn - ym, 2), 0.5);
    r = round(r * 1000) / 1000;
    printf("%.3f\n", r);
  }
}
