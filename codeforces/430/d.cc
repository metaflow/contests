#include <iostream>

using namespace std;

int v[1010][1010];
int A[1010][1010];
int B[1010][1010];
int C[1010][1010];
int D[1010][1010];

int main() {
    int rows, cols;
    cin >> rows >> cols;
    for (int r = 0; r <= rows + 1; r++)
    for (int c = 0; c <= cols + 1; c++) {
        A[r][c] = 0;
        B[r][c] = 0;
        C[r][c] = 0;
        D[r][c] = 0;
        v[r][c] = 0;
    }
    for (int r = 1; r <= rows; r++)
    for (int c = 1; c <= cols; c++) {
        cin >> v[r][c];
    }
    for (int r = 1; r <= rows; r++)
    for (int c = 1; c <= cols; c++) {
        A[r][c] = v[r][c] + max(A[r-1][c], A[r][c-1]);
    }
    for (int r = rows; r > 0; r--)
    for (int c = cols; c > 0; c--) {
        B[r][c] = v[r][c] + max(B[r+1][c], B[r][c+1]);
    }
    for (int r = rows; r > 0; r--)
    for (int c = 1; c <= cols; c++) {
        C[r][c] = v[r][c] + max(C[r+1][c], C[r][c-1]);
    }
    for (int r = 1; r <= rows; r++)
    for (int c = cols; c > 0; c--) {
        D[r][c] = v[r][c] + max(D[r-1][c], D[r][c+1]);
    }
    int m = 0;
    for (int r = 2; r < rows; r++)
    for (int c = 2; c < cols; c++) {
        int v1 = A[r-1][c] + B[r + 1][c] + C[r][c-1] + D[r][c+1];
        int v2 = A[r][c-1] + B[r][c+1] + C[r+1][c] + D[r-1][c];
        m = max(m, max(v1, v2));
    }
    cout << m << endl;
}
