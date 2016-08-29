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

const int MAX = 101;

int main() {
    int memo[MAX][MAX];
    for (int n = 0; n < MAX; n++)
    for (int k = 0; k < MAX; k++) {
        if (n == 0) {
            memo[n][k] = 1;
            continue;
        }
        if (k == 0) {
            memo[n][k] = 0;
            continue;
        }
        int t = 0;
        for (int i = 0; i <= n; i++) {
            t += memo[n - i][k - 1];
            t %= 1000000;
        }
        memo[n][k] = t;
    }

    int n, k;
    while (cin >> n >> k, n) cout << memo[n][k] << endl;
}
