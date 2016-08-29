#include <iostream>
#include <utility>

using namespace std;

const int MAX = 100;

int main() {
    int v[MAX + 1][MAX + 1];
    int n;
    cin >> n;
    for (int x = 0; x <= n; x++) {
        for (int y = 0; y <= n; y++) {
            if (x * y == 0) {
                v[x][y] = 0;
            } else {
                cin >> v[x][y];
                v[x][y] += v[x-1][y] + v[x][y-1];
                v[x][y] -= v[x-1][y-1];
            }
        }
    }
    int m = v[1][1];
    for (int x = 0; x < n; x++)
    for (int y = 0; y < n; y++)
    for (int i = x + 1; i <= n; i++)
    for (int j = y + 1; j <= n; j++) {
        int t = v[i][j] + v[x][y] - v[x][j] - v[i][y];
        m = max(m, t);
    }
    cout << m << endl;
}
