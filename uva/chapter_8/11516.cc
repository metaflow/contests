#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-10;

bool equal_double(double x, double y, double epsilon) {
  if (abs(x - y) < epsilon) return true;
  // Is x or y too close to zero?
  if (abs(x) < epsilon || abs(y) < epsilon) return false;
  // Check relative precision.
  return (abs((x - y) / x) < epsilon) && (abs((x - y) / y) < epsilon);
}

// invariant: answer is within (a, b], f(a) = false, f(b) = true
double binary_search_lower(double a, double b, function<bool(double)> f) {
  while (!equal_double(a, b, EPS)) {
    double m = (a + b) / 2;
    if (f(m)) {
      b = m;
    } else {
      a = m;
    }
  }
  return b;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int tcc;
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    int n, m;
    cin >> n >> m;
    vi houses(m);
    for (int i = 0; i < m; i++) cin >> houses[i];
    double answer = 0;
    if (n < m) {
      sort(houses.begin(), houses.end());
      answer = binary_search_lower(0, 500000, [&] (double r) {
        int c = 0;
        double position = -1e6;
        for (auto h : houses) {
          if (h <= position + r) continue;
          position = h + r;
          c++;
        }
        return c <= n;
      });
    }
    printf("%.1f\n", answer);
  }
}
