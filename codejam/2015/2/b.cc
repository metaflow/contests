#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using ll = long long;
using llu = unsigned long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vll = vector<ll>;
const int INF = numeric_limits<int>::max();
const double EPS = 1e-12;

// invariant: answer is within (a, b], f(a) = false, f(b) = true
double binary_search_lower(double a, double b, function<bool(double)> f) {
  while (round(b * 100000000) != round(a * 100000000) && b - a > 1e-8) {
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
    int n;
    double v, x;
    cin >> n >> v >> x;
    vd r(n), c(n);
    double min_rate = INF;
    for (int i = 0; i < n; i++) {
      cin >> r[i] >> c[i];
      min_rate = min(min_rate, r[i]);
    }
    auto test = [&] (double t) {
      vector<pair<double, double>> parts; // <temp, volume>
      for (int i = 0; i < n; i++) {
        parts.emplace_back(c[i], r[i] * t);
        // cerr << parts.back().first << " " << parts.back().second << " ." << endl;
      }
      sort(parts.begin(), parts.end());
      double g = 0;
      double min_t = 0;
      for (auto p : parts) {
        double y = p.second;
        if (y + g > v) {
          y = v - g;
        }
        min_t = (min_t * g + p.first * y) / (g + y);
        g += y;
        if (abs(v - g) < EPS) break;
      }
      if (v - g > EPS) {
        // cerr << v - g << endl;
        return false;
      }
      reverse(parts.begin(), parts.end());
      g = 0;
      double max_t = 0;
      for (auto p : parts) {
        double y = p.second;
        if (y + g > v) {
          y = v - g;
        }
        max_t = (max_t * g + p.first * y) / (g + y);
        g += y;
        if (abs(v - g) < EPS) break;
      }
      return (x - max_t < EPS) && (EPS > min_t - x);
    };
    double max_time = v / min_rate;
    cout << "Case #" << tc << ": ";
    if (!test(max_time)) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      cout.precision(8);
      cout << fixed << binary_search_lower(0, max_time, test) << endl;
    }
  }
}
