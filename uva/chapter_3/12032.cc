#include <vector>
#include <iostream>

using namespace std;

const int MAX = 10000000;

int main() {
    int tcc;
    scanf("%d", &tcc);
    for (int tc = 1; tc <= tcc; tc++) {
        int n;
        scanf("%d", &n);
        int p = 0;
        vector<int> ladder;
        while (n--) {
            int v;
            scanf("%d", &v);
            ladder.push_back(v - p);
            p = v;
        }
        int l = 1, r = MAX + 1;
        while (l != r) {
            int m = (l + r) / 2;
            bool f = true;

            int k = m;
            for (auto h : ladder) {
                if (h > k) {
                    f = false;
                    break;
                }
                if (h == k) k--;
            }

            if (f) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        printf("Case %d: %d\n", tc, l);
    }
    return 0;
}
