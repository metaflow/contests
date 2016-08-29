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

const int MAX = 8;
const double INF = 10000000.0d;

double memo[MAX][1 << MAX];
double D[MAX][MAX];
int memo_next[MAX][1 << MAX];

int n;

double tsp(int from, int mask) {
    if (mask == ((1 << n) - 1)) return 0.0;
    double &v = memo[from][mask];
    if (v == 0.0) {
        v = INF;
        int best_next = -1;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            double d = D[from][i];
            d += tsp(i, mask | (1 << i));
            if (d < v) {
                v = d;
                memo_next[from][mask] = i;
            }
        }
    }
    return v;
}

int main() {
    int tc = 0;
    while (cin >> n, n) {
        tc++;
        printf("**********************************************************\nNetwork #%d\n", tc);
        int x[MAX], y[MAX];
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                D[j][i] = D[i][j] = sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2));
            }
        }

        fill(&memo[0][0], &memo[MAX][0], 0.0);
        fill(&memo_next[0][0], &memo_next[MAX][0], -1);
        double best = INF;
        int current = 0;
        for (int i = 0; i < n; i++) {
            double d = tsp(i, 1 << i);
            if (d < best) {
                best = d;
                current = i;
            }
        }

        int mask = 0;
        double total = 0;
        for (int i = 0; i < n - 1; i++) {
            mask |= 1 << current;
            int next = memo_next[current][mask];
            double d = D[current][next] + 16.0;
            total += d;
            printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",
                x[current], y[current], x[next], y[next], d);
            current = next;
        }
        printf("Number of feet of cable required is %.2f.\n", total);
    }
}
