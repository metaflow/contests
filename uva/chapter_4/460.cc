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
    int a, b, c, d;
    vector<ii> x(4), y(4);
    for (int i = 0; i < 4; i++) {
      cin >> x[i].first >> y[i].first;
      x[i].second = y[i].second = i / 2;
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    if (x[0].second != x[1].second &&
        x[1].first != x[2].first &&
        y[0].second != y[1].second &&
        y[1].first != y[2].first) {
      printf("%d %d %d %d\n", x[1].first, y[1].first, x[2].first, y[2].first);
    } else {
      printf("No Overlap\n");
    }
    if (tcc) printf("\n");
  }
}
