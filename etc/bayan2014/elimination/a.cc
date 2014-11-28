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
    int n; string line;
    cin >> n >> line;
    int r = 0, p = 0, s = 0;
    for (int i = 0; i < n; i++) {
      switch (line[i]) {
        case 'R': r++; break;
        case 'P': p++; break;
        case 'S': s++; break;
      }
    }
    int best_score = -1, best_count = 0;
    if (r != 0) {
      if (best_score < s) {
        best_score = s;
        best_count = 0;
      }
      if (best_score == s) best_count += r;
    }

    if (s != 0) {
      if (best_score < p) {
        best_score = p;
        best_count = 0;
      }
      if (best_score == p) best_count += s;
    }

    if (p != 0) {
      if (best_score < r) {
        best_score = r;
        best_count = 0;
      }
      if (best_score == r) best_count += p;
    }
    printf("Case #%d:\n%d\n", tc, best_count);
  }
}
