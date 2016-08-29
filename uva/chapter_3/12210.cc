#include <stdio.h>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    int b, s;
    int tc = 0;
    while (scanf("%d%d", &b, &s), b) {
        tc++;
        printf("Case %d: ", tc);
        int m = -1;
        for (int i = 0; i < b; i++) {
            int v;
            scanf("%d", &v);
            if (m == -1 || v < m) m = v;
        }
        for (int i = 0; i < s; i++) {
            int v;
            scanf("%d", &v);
        }
        int count = max(b - s, 0);
        printf("%d", count);
        if (count) printf(" %d", m);
        putchar('\n');
    }

    return 0;
}
