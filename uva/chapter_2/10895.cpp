#include <stdio.h>

const int MAX_ROWS = 10000;
const int MAX_ELEMENTS = 1000;

int main() {
    int columns[MAX_ELEMENTS];
    int* values[MAX_ROWS];
    int* indexes[MAX_ROWS];
    int m, n;    
    for (int i = 0; i < MAX_ROWS; i++) {
        values[i] = new int[MAX_ELEMENTS];
        indexes[i] = new int[MAX_ELEMENTS];
    }
    while (scanf("%d%d", &m, &n) != EOF) {        
        int sizes[MAX_ROWS] = {0};
        for (int row = 0; row < m; row++) {
            int k;
            scanf("%d", &k);
            for (int i = 0; i < k; i++) scanf("%d", columns + i);
            for (int i = 0; i < k; i++) {
                int c = columns[i] - 1;
                scanf("%d", values[c] + sizes[c]);
                indexes[c][sizes[c]] = row;
                sizes[c]++;
            }
        }
        printf("%d %d\n", n, m);
        for (int row = 0; row < n; row++) {
            int k = sizes[row];
            printf("%d", k);
            for (int i = 0; i < k; i++) printf(" %d", indexes[row][i] + 1);
            printf("\n");
            for (int i = 0; i < k; i++) {
                if (i) printf(" ");
                printf("%d", values[row][i]);
            }
            printf("\n");
        }
    }
    return 0;
}
