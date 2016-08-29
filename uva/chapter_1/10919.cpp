#include <set>
#include <stdio.h>

using namespace std;

int main() {
    int k, m;
    while (scanf("%d", &k), k != 0) {
        scanf("%d", &m);
        set<int> taken;
        bool p = true;
        while (k--) {
            int a;
            scanf("%d", &a);
            taken.insert(a);
        }
        while (m--) {
            int c, r;
            scanf("%d%d", &c, &r);
            while (c--) {
                int a;
                scanf("%d", &a);
                if (taken.find(a) != taken.end()) {
                    r--;
                }
            }
            if (r > 0) {
                p = false;
            }
        }
        printf("%s\n", p ? "yes" : "no");
    }
    return 0;
}
