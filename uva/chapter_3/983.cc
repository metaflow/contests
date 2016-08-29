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

using ll = int;
const int MAX = 1000;

int main() {
    bool first = true;
    int n, m;
    ll M[MAX][MAX];
    ll result[MAX], row[MAX];
    while (cin >> n >> m) {
        if (!first) cout << endl;
        first = false;
        ll total = 0;
        fill(result, result + MAX, 0);
        for (int r = 0; r < n; r++) {
            ll v = 0;
            for (int c = 0; c < n; c++) {
                cin >> row[c];
                v += row[c];
                int j = c - m + 1;
                if (j >= 0) {
                    if (j) v -= row[c - m];
                    M[r][j] = v;
                    result[j] += v;
                    if (r >= m - 1) {
                        if (r >= m) result[j] -= M[r - m][j];
                        cout << result[j] << endl;
                        total += result[j];
                    }
                }
            }
        }
        cout << total << endl;
    }
}
