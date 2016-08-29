#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int case_count;
    scanf("%d", &case_count);
    while (case_count--) {
        int n;
        scanf("%d", &n);
        int min_l = 100;
        int max_l = 0;
        int v;
        while (n--) {
            scanf("%d", &v);
            min_l = min(min_l, v);
            max_l = max(max_l, v);
        }
        printf("%d\n", (max_l - min_l) * 2);
    }
    return 0;
}
