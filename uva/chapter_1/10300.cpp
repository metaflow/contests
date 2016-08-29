#include <stdio.h>

int main() {
    int cases_count;
    scanf("%d", &cases_count);
    while (cases_count--) {
        int f;
        scanf("%d", &f);
        unsigned long int a, t, x;
        unsigned long long int result = 0;
        while (f--){
            scanf("%lu%lu%lu", &a, &t, &x);
            result += a * x;
        }
        printf("%llu\n", result);
    }
    return 0;
}
