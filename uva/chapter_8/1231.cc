#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int acorns[2000][2002];

int main() {
  ios_base::sync_with_stdio(false);
  int tcc;
  cin >> tcc;
  while (tcc--) {
    int max_height, trees, fly;
    fill(&acorns[0][0], &acorns[2000][0], 0);
    cin >> trees >> max_height >> fly;
    for (int t = 0; t < trees; t++) {
      int a; cin >> a;
      while (a--) {
        int h; cin >> h;
        acorns[t][h]++;
      }
    }
    int best[2001] = {0};
    for (int h = max_height; h >= 0; h--) {
      for (int t = 0; t < trees; t++) {
        acorns[t][h] += max(acorns[t][h + 1],
          (h + fly <= max_height ? best[h + fly] : 0));
        best[h] = max(best[h], acorns[t][h]);
      }
    }
    cout << best[0] << endl;
  }
}
