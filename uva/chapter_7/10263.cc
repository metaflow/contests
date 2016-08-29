#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct dot {
  double x, y;
  double to(dot o)  {
    return pow(pow(x - o.x, 2) + pow(y - o.y, 2), 0.5);
  }

  friend ostream &operator<<( ostream &output, const dot &d )  {
     output << "(" << d.x << ", " << d.y << ")";
     return output;
  }

  const dot operator +(const dot &r) {
    dot a{x + r.x, y + r.y};
    return a;
  }
  const dot operator -(const dot &r) {
    dot a{x - r.x, y - r.y};
    return a;
  }
  const dot operator *(const double &r) {
    dot a{x * r, y * r};
    return a;
  }
};

struct V {
  dot o, s;

  const double operator *(V &r) {
    return x() * r.x() + y() * r.y();
  }
  V operator *(const double &m) {
    V r{o, (s * m)};
    return r;
  }
  const dot a() { return o; }
  const dot b() { return o + s; }
  const double x() { return s.x; }
  const double y() { return s.y; }

  friend ostream &operator<<( ostream &output, const V &v) {
     output << v.o << " -> " << v.s;
     return output;
  }
};

dot closest(dot a, dot b, dot s) {
  V A{a, b - a}, B{a, s - a};
  double p = (A * B) / (pow(A.x(), 2) + pow(A.y(), 2));
  if (p < 0) return a;
  if (p > 1) return b;
  A = A * p;
  return A.b();
}

int main() {
  dot station;
  while (cin >> station.x >> station.y) {
    int n;
    cin >> n;
    dot a;
    dot b;
    cin >> a.x >> a.y;
    dot best = a;
    double best_distance = a.to(station);
    while (n--) {
      cin >> b.x >> b.y;
      auto c = closest(a, b, station);
      // cout << a << ".." << b << " -> " << c << endl;
      double t = c.to(station);
      a = b;
      if (t > best_distance) continue;
      best_distance = t;
      best = c;
    }
    printf("%.4f\n%.4f\n", best.x, best.y);
  }
}
