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
  for (int tc = 1; tc <= tcc; tc++) {
    string s; int m;
    cin >> m >> s;
    size_t total = 0;
    int added = 0;
    for (size_t i = 0; i < s.size(); i++) {
      int d = s[i] - '0';
      if (d == 0) continue;
      if (total < i) {
        added += i - total;
        total = i;
      }
      total += d;
    }
    printf("Case #%d: %d\n", tc, added);
  }
}
