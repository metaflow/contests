#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 101;
const int MAX_D = 10002;
int n;
double b;
int points[MAX];
double T[MAX_D];

int main() {
  while (cin >> n, n) {
    for (int i = 1; i <= n; i++) cin >> points[i];
    points[0] = 0;
    int r;
    double v, e, f;
    cin >> b >> r >> v >> e >> f;
    T[0] = 0;
    for (int x = 0; x < points[n]; x++) {
      T[x + 1] = T[x];
      if (x < r) {
        T[x + 1] += 1 / (v - f * (r - x));
      } else {
        T[x + 1] += 1 / (v - e * (x - r));
      }
    }
    double best[MAX];
    best[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
      best[i] = T[points[n] - points[i]];
      for (int j = i + 1; j < n; j++) {
        best[i] = min(best[i], b + best[j] + T[points[j] - points[i]]);
      }
    }
    printf("%0.4f\n", best[0]);
  }
}
