#include <algorithm>
#include <stdio.h>

using namespace std;

int main() {
    int case_count;
    scanf("%d", &case_count);
    for (int case_num = 1; case_num <= case_count; case_num++) {
        int n;
        scanf("%d", &n);
        int mile = 0;
        int juice = 0;
        while (n--) {
            int t;
            scanf("%d", &t);
            mile += t / 30 + 1;
            juice += t / 60 + 1;
        }
        mile *= 10;
        juice *= 15;
        int m = min(mile, juice);
        printf("Case %d:%s%s %d\n",
            case_num,
            (mile == m) ? " Mile": "",
            (juice == m) ? " Juice" : "",
            m);
    }
    return 0;
}
