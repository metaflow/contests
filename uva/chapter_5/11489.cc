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
    bitset<3> b;
    b.reset();
    string s;
    cin >> s;
    int count = 0;
    int sum = 0;
    for (auto c : s) {
      if (c % 3 == 0) {
        count++;
      } else {
        sum += c;
        b[c % 3] = true;
      }
    }
    if (sum % 3 != 0) {
      if (b[sum % 3]) {
        count++;
      } else {
        count = 0;
      }
    }
    printf("Case %d: %c\n", tc, (count % 2 == 1 ? 'S' : 'T'));
  }
}
