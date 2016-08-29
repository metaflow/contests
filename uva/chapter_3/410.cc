#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int c, s;
    int tc = 0;
    while (scanf("%d%d", &c, &s) == 2) {
        tc++;
        printf("Set #%d\n", tc);
        vector<int> m(2 * c, 0);
        int sum = 0;
        for (int i = 0; i < s; i++) {
            int v;
            scanf("%d", &v);
            sum += v;
            m[i] = v;
        }
        sort(m.begin(), m.end());
        double d = 0.0d;
        for (int i = 0; i < c; i++) {
            int o = 2 * c - 1 - i;
            printf(" %d:", i);
            if (m[i] != 0) printf(" %d", m[i]);
            if (m[o] != 0) printf(" %d", m[o]);
            printf("\n");
            d += abs((m[i] + m[o]) * c - sum);
        }
        d /= c;
        printf("IMBALANCE = %.5f\n\n", d);
    }
    return 0;
}
