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
    int tcc;
    cin >> tcc;
    int a[MAX][MAX];
    while (tcc--) {
        int s, blocks;
        fill(&a[0][0], &a[MAX][0], 0);
        cin >> s >> blocks;
        while (blocks--) {
            int b, t, l, r;
            cin >> b >> l >> t >> r;
            for (int i = b; i <= t; i++)
            for (int j = l; j <= r; j++) a[i][j] = 1;
        }
        for (int i = 1; i <= s; i++)
        for (int j = 1; j <= s; j++) {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
        int best = 0;
        for (int b = 0; b < s; b++)
        for (int l = 0; l < s; l++)
        for (int t = s; t > b; t--)
        for (int r = s; r > l; r--) {
            int v = (r - l) * (t - b);
            if (v <= best) break;
            if (a[t][r] + a[b][l] - a[t][l] - a[b][r]) continue;
            best = v;
        }
        cout << best << endl;
    }
}
