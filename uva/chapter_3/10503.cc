#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const int MAX = 20;
int n, m, d1, d2, e1, e2;
int l[MAX], r[MAX];
bool used[MAX];
vector<int> index[7];

bool backtrack(int a, int step) {
    if (step == n) {
        return (a == e1);
    }
    for (auto i : index[a]) {
        if (used[i]) continue;
        used[i] = true;
        int b;
        if (l[i] == a) {
            b = r[i];
        } else {
            b = l[i];
        }
        if (backtrack(b, step + 1)) {
            return true;
        }
        used[i] = false;
    }
    return false;
}

int main() {
    while (scanf("%d", &n), n != 0) {
        int m;
        scanf("%d", &m);
        scanf("%d%d%d%d", &d1, &d2, &e1, &e2);
        for (int i = 0; i < 7; i++) index[i].clear();
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            l[i] = a;
            r[i] = b;
            used[i] = false;
            index[a].push_back(i);
            index[b].push_back(i);
        }
        if (backtrack(d2, 0)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
