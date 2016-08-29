#include <stdio.h>

int main() {
    int case_count;
    scanf("%d", &case_count);
    while (case_count--) {
        int m, n;
        scanf("%d%d", &m, &n);
        printf("%d\n", (m / 3) * (n / 3));
    }
    return 0;
}
