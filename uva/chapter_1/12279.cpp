#include <stdio.h>

int main() {
    int n;
    int case_number = 0;
    while (scanf("%d", &n), n) {
        int count = n;
        int v;
        while (count--) {
            scanf("%d", &v);
            if (v == 0) n -= 2;
        }
        printf("Case %d: %d\n", ++case_number, n);
    }
    return 0;
}
