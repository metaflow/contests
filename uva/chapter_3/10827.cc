#include <iostream>
#include <utility>

using namespace std;

const int MAX = 200;

int main() {
    int tcc;
    cin >> tcc;
    int a[MAX][MAX];
    while (tcc--) {
        int n;
        cin >> n;
        for (int x = 0; x <= n; x++)
        for (int y = 0; y <= n; y++) {
            if (x * y == 0) {
                a[x][y] = 0;
                continue;
            }
            int t;
            cin >> t;
            a[x][y] = a[x+n][y] = a[x][y+n] = a[x+n][y+n] = t;
        }
        for (int x = 1; x <= 2*n; x++)
        for (int y = 1; y <= 2*n; y++) {
            a[x][y] += a[x-1][y] + a[x][y-1] - a[x-1][y-1];
        }
        int m = a[1][1];
        for (int x = 0; x < n; x++)
        for (int y = 0; y < n; y++)
        for (int i = x + 1; i < x + 1 + n; i++)
        for (int j = y + 1; j < y + 1 + n; j++) {
            m = max(m, a[i][j] - a[x][j] - a[i][y] + a[x][y]);
        }
        cout << m << endl;
    }
}
