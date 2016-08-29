#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  ios_base::sync_with_stdio(false);
  while (cin >> n, n > 0) {
    vector<bool> row_sum(n, true), column_sum(n, true);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int a;
        cin >> a;
        if (a == 0) continue;
        row_sum[i] = !row_sum[i];
        column_sum[j] = !column_sum[j];
      }
    }
    int corrupted_row, corrupted_row_count = 0,
    corrupted_column, corrupted_column_count = 0;
    for (int i = 0; i < n; i++) {
      if (!row_sum[i]) {
        corrupted_row = i;
        corrupted_row_count++;
      }
      if (!column_sum[i]) {
        corrupted_column = i;
        corrupted_column_count++;
      }
    }
    if (corrupted_row_count == 0 && corrupted_column_count == 0) {
      printf("OK\n");
    } else {
      if (corrupted_row_count == 1 && corrupted_column_count == 1) {
        printf("Change bit (%d,%d)\n",
          corrupted_row + 1, corrupted_column + 1);
      } else {
        printf("Corrupt\n");
      }
    }
  }
}
