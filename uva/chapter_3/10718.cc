#include <stdio.h>

typedef unsigned int ui;

int main() {
    ui m, l, u;
    while (scanf("%u%u%u", &m, &l, &u) == 3) {
        ui a = 0;
        for (int i = 31; i >= 0; i--) {
            ui p = a | (1 << i);
            ui ll = (l >> i);
            ui uu = (u >> i);
            if ((m >> i) & 1) {
                ui x = (a >> i);
                if (x >= ll && x <= uu) continue;
            } else {
                ui x = (p >> i);
                if (x < ll || x > uu) continue;
            }
            a = p;
        }
        printf("%u\n", a);
    }
    return 0;
}
