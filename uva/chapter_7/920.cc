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
    int n;
    cin >> n;
    vector<ii> p;
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      p.emplace_back(x, y);
    }
    sort(p.begin(), p.end());
    auto it = p.crbegin();
    int x, y, top;
    x = it->first;
    y = top = it->second;
    double length = 0;
    for (; it != p.crend(); it++) {
      if (it->second > top) {
        length += sqrt(pow(it->first - x, 2) + pow(it->second - y, 2))
        * (it->second - top) / (double)(it->second - y);
        top = it->second;
      }
      x = it->first;
      y = it->second;
    }
    printf("%.2f\n", length);
  }
}
