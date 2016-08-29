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
    int n, p;
    cin >> n >> p;
    vi v(p);
    for (auto &a : v) cin >> a;
    int count = 0;
    for (int i = 1; i <= n; i++) {
      if ((i % 7 == 0) || (i % 7 == 6)) continue;
      for (auto h : v) {
        if (i % h == 0) {
          count++;
          break;
        }
      }
    }
    cout << count << endl;
  }
}
