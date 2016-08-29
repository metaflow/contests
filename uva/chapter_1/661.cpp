#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, m, c;
    int case_n = 0;
    while (scanf("%d%d%d", &n, &m, &c), n != 0) {
        case_n++;
        int* v = new int[n];
        int s = 0; // check range
        int max_s = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", v + i);
        }
        while (m) {
            int i;
            scanf("%d", &i);
            i--;
            s += v[i];
            max_s = max(s, max_s);
            v[i] = -v[i];
            m--;
        }
        printf("Sequence %d\n", case_n);
        if (max_s > c) {
            printf("Fuse was blown.\n");
        } else {
            printf("Fuse was not blown.\n");
            printf("Maximal power consumption was %d amperes.\n", max_s);
        }
        printf("\n");
    }
    return 0;
}
