#include <stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int v[101];
    int c[101];
    for (int i = 0; i < n; i++) {
        scanf("%d", v + i);
    }
    int f = 0;
    for (int x = 0; x <= 100; x++) {
        for (int i = 0; i < n; i++) {
            if (v[i] == x) {
                c[i] = f;
                f = (f + 1) % 2;
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (i) putchar(' ');
        printf("%d", c[i]);
    }
    putchar('\n');
}
