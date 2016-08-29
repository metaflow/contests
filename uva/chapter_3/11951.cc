#include <iostream>

using namespace std;

const int MAX = 101;
int a[MAX][MAX];

int main() {
    int tcc;
    cin >> tcc;
    for (int tc = 1; tc <= tcc; tc++) {
        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0) {
                    a[i][j] = 0;
                    continue;
                }
                cin >> a[i][j];
                a[i][j] += a[i-1][j];
            }
        }
        int best_area = 0;
        int best_price;
        for (int i = 0; i < n; i++) {
            for (int t = i + 1; t <= n; t++) {
                int s = 0;
                int l = 0;
                for (int r = 0; r < m; r++) {
                    s += a[t][r] - a[i][r];
                    while (s > k) {
                        s -= a[t][l] - a[i][l];
                        l++;
                    }
                    int area = (t - i) * (r - l + 1);
                    if (area > best_area ||
                        (area == best_area && s < best_price)) {
                        best_area = area;
                        best_price = s;
                    }
                }
            }
        }
        printf("Case #%d: %d %d\n", tc, best_area, best_price);
    }
}
