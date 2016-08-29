#include <iostream>
#include <utility>


using namespace std;

const int MAX = 1100;

int c[MAX], s[MAX];

bool backtrack(int up, int left) {
    if (left == 0) {
        bool f = true;
        for (int i = MAX - 1; i > 0; i--) {
            for (int j = 0; j < s[i]; j++) {
                if (!f) printf("+");
                f = false;
                printf("%d", i);
            }
        }
        printf("\n");
        return true;
    }
    if (left < 0) return false;
    while (up > 0 && c[up] == 0) up--;
    if (up == 0) return false;
    bool f = false;
    for (int i = c[up]; i >= 0; i--) {
        s[up] = i;
        f = f | backtrack(up - 1, left - i * up);
    }
    return f;
}

int main() {
    int t, n;
    while (scanf("%d%d", &t, &n), t != 0) {
        fill(c, c + MAX, 0);
        fill(s, s + MAX, 0);
        for (int i = 0; i < n; i++) {
            int v;
            scanf("%d", &v);
            c[v]++;
        }
        printf("Sums of %d:\n", t);
        if (!backtrack(MAX - 1, t)) {
            printf("NONE\n");
        }
    }
}
