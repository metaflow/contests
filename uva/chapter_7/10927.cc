#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

struct point {
  ll x, y, d, h, _x, _y;
  friend ostream& operator<<(ostream& os, const point& p) {
    return os << "(" << p._x << " " << p._y << " " << p.d << ')';
  };
};

ll gcd(ll x, ll y) {
  if (y == 0) return x;
  return gcd(y, x % y);
}


int main() {
  int n;
  int tc = 0;
  while (scanf("%d", &n), n) {
    tc++;
    printf("Data set %d:\n", tc);
    vector<point> v(n);
    for (int i = 0; i < n; i++) {
      point &p = v[i];
      scanf("%lld%lld%lld", &p.x, &p.y, &p.h);
      // cin >> p.x >> p.y >> p.h;
      p.d = p.x * p.x + p.y * p.y;
      ll g = gcd(abs(p.x), abs(p.y));
      p._x = p.x / g;
      p._y = p.y / g;
    }
    sort(v.begin(), v.end(), [] (const point &a, const point &b) -> bool {
      if (a._x != b._x) return a._x < b._x;
      if (a._y != b._y) return a._y < b._y;
      return a.d < b.d;
    });
    ll h = 0;
    vector<pair<ll,ll>> answer;
    for (int i = 1; i < n; i++) {
      if (v[i]._x != v[i - 1]._x || v[i]._y != v[i - 1]._y) {
        h = 0;
        continue;
      }
      h = max(h, v[i - 1].h);
      if (h < v[i].h) continue;
      answer.emplace_back(v[i].x, v[i].y);
    }
    if (answer.empty()) {
      printf("All the lights are visible.\n");
    } else {
      sort(answer.begin(), answer.end());
      printf("Some lights are not visible:\n");
      for (size_t i = 0; i < answer.size() - 1; i++) {
        printf("x = %lld, y = %lld;\n",
          answer[i].first, answer[i].second);
      }
      printf("x = %lld, y = %lld.\n",
        answer.back().first, answer.back().second);
    }
  }
}

