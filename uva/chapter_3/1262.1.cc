#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const int ROWS = 6;
const int COLS = 5;


int main() {
    int tcc;
    scanf("%d", &tcc);
    while (tcc--) {
        int k;
        scanf("%d", &k);
        char a[COLS][ROWS], p[COLS][ROWS];
        int size[COLS] = {0};
        for (int i = 0; i < ROWS; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < COLS; j++) {
                a[j][i] = s[j];
            }
        }
        for (int i = 0; i < ROWS; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < COLS; j++) {
                for (int m = 0; m < ROWS; m++) {
                    if (a[j][m] != s[j]) continue;
                    bool f = false;
                    for (int r = 0; r < size[j]; r++) {
                        if (p[j][r] != s[j]) continue;
                        f = true;
                        break;
                    }
                    if (!f) {
                        p[j][size[j]] = s[j];
                        size[j]++;
                    }
                    break;
                }
            }
        }
        for (int i = 0; i < COLS; i++) {
            sort(p[i], p[i] + size[i]);
        }
        int L[COLS];
        L[COLS - 1] = 1;
        for (int i = COLS - 2; i >= 0; i--) {
            L[i] = size[i + 1] * L[i + 1];
        }
        if (L[0] * size[0] >= k) {
            int w = 0;
            for (int i = 0; i < COLS; i++) {
                int j = 0;
                while (w + L[i] < k) {
                    j++;
                    w += L[i];
                }
                putchar(p[i][j]);
            }
            putchar('\n');
        } else {
            puts("NO");
        }
    }
}
