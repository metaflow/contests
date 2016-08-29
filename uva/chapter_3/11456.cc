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

struct train {
    int left, right, length;
};

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        int n;
        cin >> n;
        vector<int> weights(n);

        for (int i = 0; i < n; i++) {
            cin >> weights[i];
        }

        reverse(weights.begin(), weights.end());

        //vector<int> lds(n, 1);
        //vector<int> lis(n ,1);
        vector<int> inc, dec;

        int best = 0;
        for (int i = 0; i < n; i++) {
            int length = -1;
            int w = weights[i];
            auto it = lower_bound(inc.begin(), inc.end(), w);
            if (it == inc.end()) {
                inc.push_back(w);
                it = inc.end() - 1;
            }
            length += it - inc.begin() + 1;
            if (w < *it) *it = w;

            w = -w;
            it = lower_bound(dec.begin(), dec.end(), w);
            if (it == dec.end()) {
                dec.push_back(w);
                it = dec.end() - 1;
            }
            if (w < *it) *it = w;
            length += it - dec.begin() + 1;
            best = max(best, length);
        }
        cout << best << endl;
    }
}
