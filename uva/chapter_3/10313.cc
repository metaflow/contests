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
using llu = unsigned long long;

const int MAX_COIN = 300;
const int MAX_WAYS = MAX_COIN + 1;

bool next_int(int &i) {
    char s[10];
    int idx = 0;
    while (true) {
        char c = getchar();
        switch (c) {
            case '\n':
            case ' ':
            case EOF:
                if (idx) {
                    s[idx] = '\0';
                    i = atoi(s);
                }
                return c == ' ';
            default:
                s[idx++] = c;
                continue;
        }
    }
}

int main() {
    llu ways[MAX_COIN + 1][MAX_WAYS + 1]; // SUM | number of coins
    fill(&ways[0][0], &ways[MAX_COIN + 1][0], 0);
    ways[0][0] = 1;
    for (int coin = 1; coin <= MAX_COIN; coin++) {
        for (int sum = coin; sum <= MAX_COIN; sum++) {
            for (int n = 1; n <= MAX_WAYS; n++) {
                ways[sum][n] += ways[sum - coin][n - 1];
            }
        }
    }
    for (int sum = 0; sum <= MAX_COIN; sum++)
    for (int n = 1; n <= MAX_WAYS; n++) {
        ways[sum][n] += ways[sum][n - 1];
    }
    int n, l1, l2;
    while (true) {
        n = -1;
        l1 = 0;
        if (next_int(n)) {
            if (next_int(l2)) {
                l1 = l2;
                next_int(l2);
            }
        } else {
            l2 = n;
        }

        if (n == -1) break;
        if (n == 0) {
            if (l1 == 0) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        } else {
            if (l1) l1--;
            l2 = min(n, l2);
            l1 = min(n, l1);
            cout << (ways[n][l2] - ways[n][l1]) << endl;
        }
    }
}
