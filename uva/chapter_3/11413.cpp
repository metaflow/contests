#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        int v[n];
        int sum = 0;
        int max_v = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", v + i);
            max_v = max(max_v, v[i]);
            sum += v[i];
        }
        if (m > n) {
            printf("%d\n", max_v);
        } else {
            int l = max_v;
            int r = sum;
            while (l != r) {
                int t = (r + l) / 2;
                int count = 1;
                bool pass = true;
                int volume = 0;
                for (int i = 0; i < n; i++) {
                    if (v[i] + volume > t) {
                        count++;
                        if (count > m) break;
                        volume = 0;
                    }
                    volume += v[i];
                }
                if (count > m) {
                    l = t + 1;
                } else {
                    r = t;
                }
            }
            printf("%d\n", l);
        }
    }
    return 0;
}
