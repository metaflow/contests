#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct bag {
    int size, index, level, next;
    bool operator < (const bag &b) const {
        return size < b.size;
    }
};

int main() {
    bool first = true;
    int n;
    while (scanf("%d", &n), n) {
        if (!first) putchar('\n');
        first = false;
        vector<bag> bags;
        while (n--) {
            bag b;
            b.level = 0;
            b.next = -1;
            scanf("%d", &(b.size));
            bags.push_back(b);
        }
        sort(bags.begin(), bags.end());
        vector<bag> r;
        for (int i = 0; i < bags.size(); i++) {
            bag &b = bags[i];
            b.index = i;
            auto ib = lower_bound(r.begin(), r.end(), b);
            auto ibest = r.end();
            int m = 10000;
            for (auto ii = r.begin(); ii != ib; ii++) {
                if (ii->level < m) {
                    ibest = ii;
                    m = ii->level;
                }
            }
            if (ibest != r.end()) {
                b.level = ibest->level + 1;
                b.next = ibest->index;
                r.erase(ibest);
            }
            r.push_back(b);
        }
        printf("%lu\n", r.size());
        for (auto ib : r) {
            int i = ib.index;
            while (true) {
                bag &b = bags[i];
                printf("%d", b.size);
                i = b.next;
                if (i == -1) break;
                putchar(' ');
            }
            putchar('\n');
        }
    }
    return 0;
}
