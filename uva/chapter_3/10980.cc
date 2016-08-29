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

bool next_int(int &k) {
    char buf[80];
    int pos = 0;
    while (true) {
        char c = getchar();
        switch (c) {
            case ' ':
                if (pos == 0) continue;
            case '\n':
                buf[pos++] = '\0';
                k = atoi(buf);
                return c == ' ';
            default:
                buf[pos++] = c;
                break;
        }
    }
    return false;
}

int main() {
    int tc = 0;
    int count;
    double price;
    while (scanf("%lf%d\n", &price, &count) == 2) {
        printf("Case %d:\n", ++tc);
        double best_buy[MAX];
        int pack = 1;
        fill_n(best_buy, MAX, 1e7);
        best_buy[0] = 0;
        for (int i = 0; i <= count; i++) {
            // cerr << "price " << price << " pack " << pack << endl;
            for (int j = 1; j < MAX; j++) {
                for (int k = 1; k <= pack && k <= j; k++) {
                    best_buy[j] = min(best_buy[j], best_buy[j - k] + price);
                }
            }
            if (i != count) scanf("%d%lf\n", &pack, &price);
        }

        while (true) {
            int k;
            bool ok = next_int(k);
            printf("Buy %d for $%.2lf\n", k, round(best_buy[k] * 100) / 100);
            if (!ok) break;
        }
    }
}
