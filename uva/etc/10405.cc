#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 1010;

int main() {
  cout.sync_with_stdio(false);
  int m[MAX][MAX];
  string a, b;
  while (getline(cin, a) && getline(cin, b)) {
    fill(&m[0][0], &m[MAX][0], 0);
    for (size_t i = 1; i <= a.size(); i++) {
      for (size_t j = 1; j <= b.size(); j++) {
        auto &r = m[i][j];
        if (a[i-1] == b[j-1]) {
          r = m[i - 1][j - 1] + 1;
        } else {
          r = max(m[i-1][j], r);
          r = max(m[i][j-1], r);
        }
      }
    }
    cout << m[a.size()][b.size()] << endl;
  }
}
