#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 100;

int main() {
  int rows, columns;
  int A[MAX][MAX], B[MAX][MAX];
  while (cin >> rows >> columns) {
    fill(&A[0][0], &A[MAX][0], 1);
    fill(&B[0][0], &B[MAX][0], 0);
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < columns; c++) {
        int i; cin >> i;
        B[r][c] = i;
        if (i == 0) {
          for (int j = 0; j < rows; j++) A[j][c] = 0;
          for (int j = 0; j < columns; j++) A[r][j] = 0;
        }
      }
    }
    bool ok = true;
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < columns; c++) {
        int v = 0;
        for (int j = 0; j < rows; j++) if (A[j][c]) v = 1;
        for (int j = 0; j < columns; j++) if (A[r][j]) v = 1;
        if (B[r][c] != v) ok = false;
      }
    }
    if (ok) {
      cout << "YES" << endl;
      for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
          if (c) cout << " ";
          cout << A[r][c];
        }
        cout << endl;
      }
    } else {
      cout << "NO" << endl;
    }
  }
}
