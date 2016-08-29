#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_N = 51;
const int MAX_P = 13;
const int INF = 10000000;

int D[MAX_N][MAX_N];
int memo[MAX_P][1 << MAX_P];
int index[MAX_P], value[MAX_P];
int n, p;

void fw() {
    for (int i = 0; i < n; i++) D[i][i] = 0;
    for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
}

int tsp(int idx, int mask) {
    if (mask == (1 << p) - 1) return -D[0][index[idx]];
    int &v = memo[idx][mask];
    if (v == -1) {
        v = -D[0][index[idx]];
        for (int i = 0; i < p; i++) {
            if (mask & (1 << i)) continue;
            int t = value[i]
                    - D[index[i]][index[idx]]
                    + tsp(i, mask | (1 << i));
            v = max(v, t);
        }
    }
    return v;
}

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        int m;
        cin >> n >> m;
        n++;
        // cerr << "n " << n << " m " << m << endl;
        fill(&D[0][0], &D[MAX_N][0], INF);
        while (m--) {
            int a, b;
            double c;
            cin >> a >> b >> c;
            int t = round(c * 100);
            t = min(t, D[a][b]);
            D[a][b] = D[b][a] = t;
        }
        fw();
        cin >> p;
        p++;
        value[0] = 0;
        index[0] = 0;
        for (int i = 1; i < p; i++) {
            double c;
            cin >> index[i] >> c;
            value[i] = round(c * 100);
        }
        fill(&memo[0][0], &memo[MAX_P][0], -1);
        int best = tsp(0, 1);
        if (best > 0) {
            printf("Daniel can save $%.2f\n", double(best) / 100);
        } else {
            printf("Don't leave the house\n");
        }
    }
}
