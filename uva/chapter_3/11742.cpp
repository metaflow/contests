#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m), !(n == 0 && m == 0)) {
        vector<int> s(n);
        for (int i = 0; i < n; i++) {
            s[i] = i;
        }
        int a[m], b[m], c[m];
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", a+i, b+i, c+i);
        }
        int count = 0;
        do {
            bool fit = true;
            for (int i = 0; i < m; i++) {
                int x, y;
                for (int j = 0; j < n; j++) {
                    if (s[j] == a[i]) x = j;
                    if (s[j] == b[i]) y = j;
                }
                if (c[i] > 0) {
                   fit = abs(x - y) <= c[i];
                } else {
                   fit = abs(x - y) >= -c[i];
                }
                if (!fit) break;
            }
            if (fit) count++;
        } while (next_permutation(s.begin(), s.end()));
        printf("%d\n", count);
    }
    return 0;
}
