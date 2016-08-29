#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, d, r;
    int a[100], b[100];
    while (scanf("%d%d%d", &n, &d, &r), n + d + r != 0) {
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        for (int i = 0; i < n; i++) scanf("%d", b + i);
        sort(a, a + n);
        sort(b, b + n);
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int v = a[i] + b[n - 1 - i] - d;
            if (v <= 0) continue;
            sum += v;
        }
        printf("%d\n", sum * r);
    }
    return 0;
}
