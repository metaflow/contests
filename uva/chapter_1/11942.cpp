#include <stdio.h>

int main() {
    int case_count;
    scanf("%d", &case_count);
    printf("Lumberjacks:\n");
    while (case_count--) {
        bool asc = true;
        bool dec = true;
        int current, next;
        scanf("%d", &current);
        for (int i = 0; i < 9; i++) {
            scanf("%d", &next);
            if (next > current) dec = false;
            if (next < current) asc = false;
            current = next;
        }
        bool ordered = (asc || dec);
        printf("%s\n", ordered ? "Ordered" : "Unordered");
    }
    return 0;
}
