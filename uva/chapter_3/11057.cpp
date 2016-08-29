#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    int v[10001];
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            scanf("%d", v + i);
        }
        sort(v, v + n);
        int m;
        cin >> m;
        int l = 0, u = n;
        int p = m / 2;
        while (l < u) {
            int k = (l + u) / 2;
            if (v[k] < p) {
                l = k + 1;
            } else {
                u = k;
            }
        }
        if (v[l] > p) l--;
        u = l + 1;
        while (true) {
            int t = m - v[l];
            while (v[u] < t) u++;
            if (v[u] == t) break;
            l--;
        }
        printf("Peter should buy books whose prices are %d and %d.\n\n", v[l], v[u]);
    }
    return 0;
}
