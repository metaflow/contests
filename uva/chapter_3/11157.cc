#include <iostream>
#include <vector>
#include <utility>

using namespace std;

char next() {
    char r;
    while (true) {
        r = getchar();
        if (r == ' ' || r == '\n') continue;
        return r;
    }
    return r;
}

int main() {
    int tcc;
    cin >> tcc;
    for (int tc = 1; tc <= tcc; tc++) {
        int n, d;
        vector<int> r, t;
        scanf("%d%d", &n, &d);
        r.push_back(0);
        t.push_back(0);
        for (int i = 0; i < n; i++) {
            char size = next();
            next();
            int v;
            scanf("%d", &v);
            r.push_back(v);
            t.push_back(size == 'B' ? 0 : 1);
        }
        r.push_back(d);
        t.push_back(0);
        int i = 0;
        for (int i = 1; i <= n; i++) {
            if (t[i] == 0) continue;
            if (t[i - 1] == 1) t[i] = -1;
        }
        int p = 0;
        int m = 0;
        for (int i = 1; i < r.size(); i++) {
            if (t[i] == -1) continue;
            m = max(m, r[i] - p);
            p = r[i];
        }
        p = 0;
        for (int i = 1; i < r.size(); i++) {
            if (t[i] == 1) continue;
            m = max(m, r[i] - p);
            p = r[i];
        }
        printf("Case %d: %d\n", tc, m);
    }
}
