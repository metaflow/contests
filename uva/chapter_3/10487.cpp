#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    int n;
    int tc = 0;
    while (scanf("%d", &n), n != 0) {
        tc++;
        printf("Case %d:\n", tc);
        vector<int> v;
        for (int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            v.push_back(a);
        }
        sort(v.begin(), v.end());
        int m;
        scanf("%d", &m);
        while (m--) {
            int s;
            scanf("%d", &s);
            int best = -1;
            for (auto it = v.begin(); it != v.end(); it++) {
                for (auto jt = it + 1; jt != v.end(); jt++) {
                    int t = *jt + *it;
                    if (abs(best - s) > abs(t - s) || best == -1) {
                        best = t;
                    } else {
                        if (t > s) break;
                    }
                }
            }
            printf("Closest sum to %d is %d.\n", s, best);
        }
    }
    return 0;
}
