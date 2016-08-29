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

struct block {
    int x, y, h;
    bool operator < (const block &o) const {
        if (x == o.x) return y < o.y;
        return x < o.x;
    }
};

int main() {
    int n;
    int tc = 0;
    while (cin >> n, n) {
        tc++;
        vector<block> blocks;
        while (n--) {
            int x, y, z;
            cin >> x >> y >> z;
            block b;
            b.x = min(x, y);
            b.y = max(x, y);
            b.h = z;
            blocks.push_back(b);
            b.x = min(x, z);
            b.y = max(x, z);
            b.h = y;
            blocks.push_back(b);
            b.x = min(y, z);
            b.y = max(y, z);
            b.h = x;
            blocks.push_back(b);
        }
        sort(blocks.begin(), blocks.end());
        // for (auto b : blocks) {
        //     printf("%d %d %d\n", b.x, b.y, b.h);
        // }
        // printf("\n");
        int best = 0;
        for (int i = 1; i < blocks.size(); i++) {
            block &b = blocks[i];
            int h = 0;
            for (int j = 0; j < i; j++) {
                if (blocks[j].x < b.x && blocks[j].y < b.y) {
                    h = max(h, blocks[j].h);
                }
            }
            b.h += h;
            best = max(best, b.h);
        }
        printf("Case %d: maximum height = %d\n", tc, best);
    }
}
