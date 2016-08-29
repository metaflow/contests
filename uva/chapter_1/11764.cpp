#include <stdio.h>

int main() {
    int case_count;
    scanf("%d", &case_count);
    for (int ii = 1; ii <= case_count; ii++) {
        int n;
        scanf("%d", &n);
        int low = 0;
        int high = 0;
        int current = -1;
        int next;
        while (n--) {
            scanf("%d", &next);
            if (current != -1) {
                if (next < current) low++;
                if (next > current) high++;
            }
            current = next;
        }
        printf("Case %d: %d %d\n", ii, high, low);
    }
    return 0;
}
