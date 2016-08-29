#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAX = 20;

struct common {
    int used;
    bool stations[MAX];
    int size;
};

int station[MAX];
common cc[MAX];
int selection[MAX], best_selection[MAX];
int m, n;
int t;
int best;

void read_common(int idx) {
    int c;
    scanf("%d", &c);
    fill(cc[idx].stations, cc[idx].stations + MAX, false);
    for (int i = 0; i < c; i++) {
        int v;
        scanf("%d", &v);
        cc[idx].stations[v - 1] = true;
    }
    scanf("%d", &(cc[idx].size));
}


void recourse(int from, int count, int sum) {
    if (count == n) {
        if (sum > best) {
            best = sum;
            for (int i = 0; i < n; i++) {
                best_selection[i] = selection[i];
            }
        }
        return;
    }
    if (from > m - (n - count)) return;
    for (int i = from; i < m; i++) {
        int d = station[i];
        for (int j = 0; j < t; j++) {
            if (cc[j].stations[i]) {
                if (cc[j].used != 0) d -= cc[j].size;
                cc[j].used++;
            }
        }
        selection[count] = i;
        recourse(i + 1, count + 1, sum + d);
        for (int j = 0; j < t; j++) {
            if (cc[j].stations[i]) {
                cc[j].used--;
            }
        }
    }
}

void solve() {
    best = 0;
    for (int i = 0; i < MAX; i++) {
        cc[i].used = 0;
    }
    recourse(0, 0, 0);
}

int main() {
    int tc = 0;
    while (scanf("%d%d", &m, &n), m != 0) {
        tc++;
        for (int i = 0; i < m; i++) {
            scanf("%d", station + i);
        }
        scanf("%d", &t);
        for (int i = 0; i < t; i++) {
            read_common(i);
        }
        solve();
        printf("Case Number  %d\n", tc);
        printf("Number of Customers: %d\n", best);
        printf("Locations recommended:");
        for (int i = 0; i < n; i++) {
            printf(" %d", best_selection[i] + 1);
        }
        printf("\n\n");
    }
    return 0;
}
