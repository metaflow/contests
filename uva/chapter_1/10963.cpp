#include <stdio.h>

int main() {
    int cases_count;
    scanf("%d", &cases_count);
    while (cases_count--) {
        int a, b, columns, gap = -1;
        bool closed = true;
        scanf("%d", &columns);
        while (columns--) {
            scanf("%d%d", &a, &b);
            if (gap == -1) gap = a - b;
            closed &= gap == (a-b);
        }
        printf("%s\n", closed ? "yes" : "no");
        if (cases_count) printf("\n");
    }
    return 0;
}
