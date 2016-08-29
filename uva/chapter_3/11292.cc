#include <algorithm>
#include <iostream>

using namespace std;

const int MAX = 20000;

int main() {
    int dc, kc;
    int dragons[MAX], knights[MAX];
    while (scanf("%d%d", &dc, &kc), dc != 0) {
        for (int i = 0; i < dc; i++) scanf("%d", dragons + i);
        for (int i = 0; i < kc; i++) scanf("%d", knights + i);
        sort(dragons, dragons + dc);
        sort(knights, knights + kc);
        int k = 0;
        int sum = 0;
        bool doomed = false;
        for (int i = 0; i < dc; i++) {
            while (k < kc && knights[k] < dragons[i]) k++;
            if (k >= kc) {
                doomed = true;
                break;
            }
            sum += knights[k];
            k++;
        }
        if (doomed) {
            printf("Loowater is doomed!\n");
        } else {
            printf("%d\n", sum);
        }
    }
    return 0;
}
