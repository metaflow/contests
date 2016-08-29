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

const int MAX = 11;
const int INF = 1000000;

int x[MAX], y[MAX];
int n;
int memo[MAX][1 << MAX];

int distance(int i, int j) {
    return abs(x[i] - x[j]) + abs(y[i] - y[j]);
}

int tsp(int from, int mask) {
    if (mask == (1 << n) - 1) return distance(from, 0);
    int &v = memo[from][mask];
    if (v == 0) {
        v = INF;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            v = min(v, distance(from, i) + tsp(i, mask | (1 << i)));
        }
    }
    return v;
}

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        cin >> x[0] >> x[0] >> x[0] >> y[0];
        cin >> n;
        n++;
        for (int i = 1; i < n; i++) cin >> x[i] >> y[i];
        fill(&memo[0][0], &memo[MAX][0], 0);
        printf("The shortest path has length %d\n", tsp(0, 1));
    }
}
