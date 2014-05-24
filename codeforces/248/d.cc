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

using vi = vector<int>;
using vvi = vector<vi>;

void get_width(vi &a, int &l, int &r, int v) {
    auto it = lower_bound(a.begin(), a.end(), v);
    if (it != a.end() && *it == v) {
        l = r;
        return;
    }
    if (it != a.begin()) l = max(l, *(it - 1));
    if (it != a.end()) r = min(r, *it);
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vvi rows(n), cols(m);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int v;
            cin >> v;
            if (v) continue;
            rows[r].push_back(c);
            cols[c].push_back(r);
        }
    }
    while (q--) {
        int p, x, y;
        cin >> p >> x >> y;
        x--;
        y--;
        if (p == 1) {
            auto it = lower_bound(rows[x].begin(), rows[x].end(), y);
            if (it != rows[x].end() && *it == y) {
                rows[x].erase(it);
            } else {
                rows[x].insert(it, y);
            }
            it = lower_bound(cols[y].begin(), cols[y].end(), x);
            if (it != cols[y].end() && *it == x) {
                cols[y].erase(it);
            } else {
                cols[y].insert(it, x);
            }
        } else {
            int best = 0;
            int l = -1, r = m;
            for (int i = x; i >= 0; i--) {
                get_width(rows[i], l, r, y);
                if (r - l <= 0) break;
                best = max(best, (x - i + 1) * (r - l - 1));
            }
            l = -1;
            r = m;
            for (int i = x; i < n; i++) {
                get_width(rows[i], l, r, y);
                if (r - l <= 0) break;
                best = max(best, (i - x + 1) * (r - l - 1));
            }
            l = -1;
            r = n;
            for (int i = y; i >= 0; i--) {
                get_width(cols[i], l, r, x);
                if (r - l <= 0) break;
                best = max(best, (y - i + 1) * (r - l - 1));
            }
            l = -1;
            r = n;
            for (int i = y; i < m; i++) {
                get_width(cols[i], l, r, x);
                if (r - l <= 0) break;
                best = max(best, (i - y + 1) * (r - l - 1));
            }
            cout << best << endl;
        }
    }
}
