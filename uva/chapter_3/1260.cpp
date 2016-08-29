#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int tcc;
    scanf("%d", &tcc);
    while (tcc--) {
        int k;
        scanf("%d", &k);
        int r = 0;
        vector<int> amounts;
        while (k--) {
            int a;
            scanf("%d", &a);
            auto it = upper_bound(amounts.begin(), amounts.end(), a);
            r += it - amounts.begin();
            amounts.insert(it, a);
        }
        printf("%d\n", r);
    }
    return 0;
}
