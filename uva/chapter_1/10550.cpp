#include <stdio.h>

int main() {
    int a, b, c, d;
    while(scanf("%d%d%d%d", &a, &b, &c, &d), a + b + c + d) {
        int r = 80; // 2 turns
        // clockwise up to a -> b
        r += (a + 40 - b) % 40;
        r += 40; // 1 turn
        // counter clockwise b -> c
        r += (c + 40 - b) % 40;
        // clockwise c -> d
        r += (c + 40 - d) % 40;
        if (c == d) r += 40;
        printf("%d\n", r * 9);
    }
    return 0;
}
