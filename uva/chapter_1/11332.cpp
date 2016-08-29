#include <stdio.h>

int main() {
    int n;
    while (scanf("%d", &n), n) {
        int m = n % 9;
        printf("%d\n", m == 0 ? 9 : m);
    }
    return 0;
}
