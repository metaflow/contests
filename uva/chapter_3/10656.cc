#include <stdio.h>

int main() {
    int n;
    while (scanf("%d", &n), n) {
        bool f = false;
        while(n--) {
            int v;
            scanf("%d", &v);
            if (v) {
                if (f) putchar(' ');
                printf("%d", v);
                f = true;
            }
        }
        if (!f) putchar('0');
        putchar('\n');
    }
    return 0;
}
