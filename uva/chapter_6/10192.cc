#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string a, b;
  int tc = 0;
  while (getline(cin, a)) {
    if (a[0] == '#') break;
    getline(cin, b);
    tc++;
    vector<int> current(a.size() + 1, 0), next_row(a.size() + 1, 0);
    for (int i = 0; i < b.size(); i++) {
      for (int j = 0; j < a.size(); j++) {
        if (a[j] == b[i]) {
          next_row[j + 1] = current[j] + 1;
        } else {
          next_row[j + 1] = max(next_row[j], current[j + 1]);
        }
      }
      current.swap(next_row);
      next_row.assign(a.size() + 1, 0);
    }
    printf("Case #%d: you can visit at most %d cities.\n",
      tc, current[a.size()]);
  }
}
