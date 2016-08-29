#include <stdio.h>

int main() {
    int r[21];
    int b, n;
    while (scanf("%d%d", &b, &n), b) {
        for (int i = 0; i < b; i++) scanf("%d", r + i + 1);
        for (int i = 0; i < n; i++) {
            int d, c, v;
            scanf("%d%d%d", &d, &c, &v);
            r[d] -= v;
            r[c] += v;
        }
        bool possible = true;
        for (int i = 0; i < b; i++) {
            if (r[i + 1] >= 0) continue;
            possible = false;
            break;
        }
        printf("%s\n", possible ? "S" : "N");
    }
    return 0;
}
