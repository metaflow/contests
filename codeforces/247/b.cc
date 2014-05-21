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

int main() {
    int g[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> g[i][j];
        }
    }
    vector<int> p = {0, 1, 2, 3 ,4};
    int best = 0;
    while (true) {
        int t = g[p[0]][p[1]] + g[p[2]][p[3]] +
                g[p[1]][p[0]] + g[p[3]][p[2]] +
                g[p[1]][p[2]] + g[p[2]][p[1]] +
                g[p[3]][p[4]] + g[p[4]][p[3]] +
                g[p[2]][p[3]] + g[p[3]][p[2]] +
                g[p[3]][p[4]] + g[p[4]][p[3]];
        best = max(best, t);
        if (!next_permutation(p.begin(), p.end())) break;
    }
    cout << best << endl;
}
