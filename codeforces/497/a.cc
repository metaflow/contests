#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n, m;
  while (cin >> n >> m) {
    vector<string> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    vi rank(n, 0);
    int skipped = 0;
    for (int p = 0; p < m; p++) {
      vi rank_new(n, 0);
      bool ok = true;
      for (int i = 0; i < n - 1; i++) {
        if (rank[i] < rank[i + 1]) {
          rank_new[i + 1] = rank_new[i] + 1;
          continue;
        }
        if (v[i][p] < v[i + 1][p]) {
          rank_new[i + 1] = rank_new[i] + 1;
          continue;
        }
        if (v[i][p] == v[i + 1][p]) {
          // rank[i] == rank[i + 1])
          rank_new[i + 1] = rank_new[i];
          continue;
        }
        //v[i][p] > v[i + 1][p] and ranks equals
        ok = false;
        break;
      }
      if (ok) {
        rank.swap(rank_new);
      } else {
        skipped++;
      }
    }
    cout << skipped << endl;
  }
}
