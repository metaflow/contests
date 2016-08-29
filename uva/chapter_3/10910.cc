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

const int MAX = 71;

int main() {
    int tcc;
    scanf("%d", &tcc);
    int w[MAX][MAX];
    fill(&w[0][0], &w[MAX][0], 0);
    for (int i = 1; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (i == 1 || j == 0) {
                w[i][j] = 1;
                continue;
            }
            for (int k = 0; k <= j; k++) w[i][j] += w[i - 1][k];
        }
    }
    while (tcc--) {
        int n, t, p;
        scanf("%d%d%d", &n, &t, &p);
        t -= n * p;
        if (t < 0) {
            printf("0\n");
        } else {
            printf("%d\n", w[n][t]);
        }
    }
}
