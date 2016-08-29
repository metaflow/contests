#include <iostream>
#include <utility>

using namespace std;

const int MAX = 8;
int M[MAX][MAX];
bool cols[MAX];
int n;

int bob(int turn) {
    if (turn == n) return 0;
    int best = -10000;
    for (int i = 0; i < n; i++) {
        if (cols[i]) continue;
        cols[i] = true;
        best = max(best, -M[turn][i] + bob(turn+1));
        cols[i] = false;
    }
    return best;
}

int main() {
    int tcc;
    scanf("%d", &tcc);
    for (int tc = 1; tc <= tcc; tc++) {
        scanf("%d", &n);
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                scanf("%d", M[r] + c);
            }
        }
        // reset solution
        fill(cols, cols + n, false);
        printf("%d\n", -bob(0));
    }
}
