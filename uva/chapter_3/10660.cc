#include <iostream>
#include <utility>

using namespace std;

const int MAX = 25;
const int L = 5;
int best_weight;
int p[MAX];
int solution[L], best_solution[L];

int weight(int k) {
    int w = 0;
    for (int i = 0; i < MAX; i++) {
        int b = 100;
        int r = i / 5;
        int c = i % 5;
        for (int j = 0; j < k; j++) {
            int rr = solution[j] / 5;
            int cc = solution[j] % 5;
            b = min(abs(rr - r) + abs(cc - c), b);
        }
        w += b * p[i];
    }
    return w;
}

void backtrack(int from, int idx) {
    if (idx == L) {
        int w = weight(L);
        if (w < best_weight || best_weight == -1) {
            best_weight = w;
            copy(solution, solution + L, best_solution);
        }
        return;
    }
    if (from + (L - idx) >= MAX) return;
    for (int i = from; i < MAX; i++) {
        solution[idx] = i;
        backtrack(i + 1, idx + 1);
    }
}

int main() {
    int tcc;
    scanf("%d", &tcc);
    for (int tc = 1; tc <= tcc; tc++) {
        fill(p, p + MAX, 0);
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            scanf("%d", p + a * 5 + b);
        }
        best_weight = -1;
        backtrack(0, 0);
        for (int i = 0; i < L; i++) {
            if (i != 0) printf(" ");
            printf("%d", best_solution[i]);
        }
        printf("\n");
    }
    return 0;
}
