#include <iostream>
#include <utility>

using namespace std;

const int MAX = 20 + 1;

int main() {
    // int v[MAX][MAX][MAX];
    long long q[MAX][MAX][MAX];
    int tcc;
    cin >> tcc;
    for (int tc = 1; tc <= tcc; tc++) {
        if (tc != 1) printf("\n");
        int a, b, c;
        cin >> a >> b >> c;
        for (int i = 0; i <= a; i++)
        for (int j = 0; j <= b; j++)
        for (int k = 0; k <= c; k++) {
            if (i * j * k == 0) {
                q[i][j][k] = 0;
                continue;
            }
            int v;
            cin >> q[i][j][k];
            q[i][j][k] += q[i-1][j][k] + q[i][j-1][k] - q[i-1][j-1][k];
        }
        long long m = q[1][1][1];
        for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++)
        for (int x = i + 1; x <= a; x++)
        for (int y = j + 1; y <= b; y++) {
            long long s = 0;
            for (int k = 1; k <= c; k++) {
                long long t = q[x][y][k] - q[i][y][k] - q[x][j][k] + q[i][j][k];
                s += t;
                m = max(m, s);
                if (s < 0) s = 0;
            }
        }
        printf("%lld\n", m);
    }
}
