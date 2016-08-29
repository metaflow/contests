#include <stdio.h>

int main () {
    int case_count;
    scanf("%d", &case_count);
    for (int c = 1; c <= case_count; c++) {
        int w, h, l;
        scanf("%d%d%d", &w, &h, &l);
        printf("Case %d: %s\n", c, ((w < 21) && (h < 21) && (l < 21)) ? "good" : "bad");
    }
    return 0;    
}
