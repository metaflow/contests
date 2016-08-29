#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int rows, cols;
    int d[1000][500];
    int s[1000];
    while (scanf("%d%d", &rows, &cols), rows) {
        fill(s, s + 1000, 0);
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int t = r - c + cols - 1;
                scanf("%d", d[t] + s[t]);
                s[t]++;
            }
        }
        int q;
        cin >> q;
        while (q--) {
            int u, l;
            scanf("%d%d", &l, &u);
            int m = 0;
            int lower = 0, upper = 0;
            for (int i = 0; i < rows + cols - 1; i++) {
                if (s[i] <= m) continue;
                if (upper != lower) {
                    for (int k = max(0, lower - 1); k < lower + 2; k++) {
                        if (k >= s[i] || d[i][k] >= l) {
                            lower = k;
                            break;
                        }
                    }
                    for (int k = max(0, upper - 1); k < upper + 2; k++) {
                        if (k >= s[i] || d[i][k] > u) {
                            upper = k;
                            break;
                        }
                    }
                } else {
                    lower = lower_bound(d[i], d[i] + s[i], l) - d[i];
                    upper = upper_bound(d[i], d[i] + s[i], u) - d[i];
                }
                m = max(m, upper - lower);
            }
            printf("%d\n", m);
        }
        puts("-");
    }
    return 0;
}
