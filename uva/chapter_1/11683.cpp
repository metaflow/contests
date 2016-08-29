#include <stdio.h>

int main() {
    int a, c;
    while (scanf("%d%d", &a, &c) == 2 && a != 0) {
        int r = 0;
        int h[c];
        for (int i = 0; i < c; i++) {
            scanf("%d", h + i);
        }
        for (int i = 1; i < c; i++) {
            int d = h[i] - h[i - 1];
            if (d > 0) {
                r += d;
            }
        }
        r += a - h[c - 1];
        printf("%d\n", r);
    }
    return 0;
}
