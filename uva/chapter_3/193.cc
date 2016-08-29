#include <iostream>
#include <vector>

using namespace std;

struct node {
    vector<int> n;
    int refs;
};

int n, best;
vector<node> G;
vector<int> solution;

void backtrack(int idx, int black_count) {
    if (idx == n) {
        if (black_count > best) {
            best = black_count;
            solution.clear();
            for (int i = 0; i < n; i++) {
                if (G[i].refs == 0) {
                    solution.push_back(i + 1);
                }
            }
        }
        return;
    }
    if (n - idx + black_count < best) return;
    node &x = G[idx];
    if (x.refs == 0) {
        //x.black = true;
        for (auto i : x.n) G[i].refs++;
        backtrack(idx + 1, black_count + 1);
        //x.black = false;
        for (auto i : x.n) G[i].refs--;
    }
    backtrack(idx + 1, black_count);
}

int main() {
    int tcc;
    scanf("%d", &tcc);
    while (tcc--) {
        int k;
        scanf("%d%d", &n, &k);
        G.clear();
        G.resize(n);
        while (k--) {
            int a, b;
            scanf("%d%d", &a, &b);
            a--;
            b--;
            G[a].n.push_back(b);
            G[b].n.push_back(a);
        }
        for (int i = 0; i < n; i++) G[i].refs = 0;
        best = 0;
        backtrack(0, 0);
        printf("%d\n", best);
        for (int i = 0; i < solution.size(); i++) {
            if (i != 0) printf(" ");
            printf("%d", solution[i]);
        }
        printf("\n");
    }
    return 0;
}
