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

void fill_lis(vi &v, vi &f) {
    vector<int> lis;
    for (int i = 0; i < v.size(); i++) {
        auto it = lower_bound(lis.begin(), lis.end(), v[i]);
        if (it == lis.end()) {
            lis.push_back(i);
            it = lis.end() - 1;
        }
        *it = v[i];
        f[i] = it - lis.begin() + 1;
    }
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> v;
        while (n--) {
            int i;
            cin >> i;
            v.push_back(i);
        }
        vector<int> ff(v.size()), rr(v.size());
        fill_lis(v, ff);
        reverse(v.begin(), v.end());
        fill_lis(v, rr);
        reverse(rr.begin(), rr.end());
        int best = 0;
        for (int i = 0; i < v.size(); i++) {
            best = max(best, min(ff[i], rr[i]));
        }
        cout << (best - 1) * 2 + 1 << endl;
    }
}
