#include <stdio.h>

int main() {
    int n;
    int first_case = true;
    while (scanf("%d", &n), n) {
        if (!first_case) printf("\n");
        bool found_solution = false;
        for (int fghij = 1234; fghij <= 98765 / n; fghij++) {
            int abcde = fghij * n;
            int used = (fghij < 10000) ? 1 : 0;
            int t = fghij; while (t) { used |= (1 << (t % 10)); t /= 10; }
            t = abcde; while (t) { used |= (1 << (t % 10)); t /= 10; }
            if (used == (1 << 10) - 1) {
                printf("%0.5d / %0.5d = %d\n", abcde, fghij, n);
                found_solution = true;
            }
        }
        if (!found_solution) printf("There are no solutions for %d.\n", n);
        first_case = false;
    }
    return 0;
}
