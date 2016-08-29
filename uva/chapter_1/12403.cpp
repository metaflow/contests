#include <stdio.h>

int main() {
    int lines;
    int total = 0;
    int v;
    scanf("%d", &lines);
    char s[30];
    while (lines--) {
        scanf("%s", s);
        if (s[0] == 'd') {
            scanf("%d", &v);
            total += v;
        } else {
            printf("%d\n", total);
        }
    }
    return 0;
}
