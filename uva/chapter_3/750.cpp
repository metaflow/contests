#include <stdio.h>
#include <cstring>
#include <algorithm>

using namespace std;

int a, b, line;
int row[8];

bool place(int c, int r) {
    for (int i = 0; i < c; i++) {
        if (row[i] == r) return false;
        if (abs(row[i] - r) == abs(i - c)) return false;
    }
    return true;
}

void backtrack(int c) {
    if (c == 8) {
        printf("%2d      %d", line, row[0] + 1);
        line++;
        for (int i = 1; i < 8; i++) {
            printf(" %d", row[i] + 1);
        }
        printf("\n");
        return;
    }
    if (c == b) {
        if (place(b, a)) {
            row[b] = a;
            backtrack(c + 1);
        }
    } else {
        for (int i = 0; i < 8; i++) {
            if (place(c, i)) {
                row[c] = i;
                backtrack(c + 1);
            }
        }
    }
}

int main() {
    int tc;
    scanf("%d", &tc);
    while (tc--) {
        scanf("%d%d", &a, &b);
        a--;
        b--;
        line = 1;
        memset(row, 0, sizeof row);
        printf("SOLN       COLUMN\n");
        printf(" #      1 2 3 4 5 6 7 8\n\n");
        backtrack(0);
        if (tc) printf("\n");
    }
    return 0;
}
