#include <iostream>

using namespace std;

int main() {
    int s, d;
    while (scanf("%d%d", &s, &d) == 2) {
        int r;
        if (d > 4*s) {
            r = 10*s - 2*d;
        } else if (2*d > 3*s) {
            r = 8*s - 4*d;
        } else if (3*d > 2*s) {
            r = 6*s - 6*d;
        } else if (4*d > s) {
            r = 3*s - 9*d;
        } else {
            r = -12 * d;
        }
        if (r >= 0) {
            printf("%d\n", r);
        } else {
            printf("Deficit\n");
        }
    }
    return 0;
}
