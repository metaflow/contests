#include <math.h>
#include <algorithm>
#include <bitset>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;
        // cout << n << ' ' << m << endl;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        sort(v.begin(), v.end());
        int low = 0;
        int len = v[n-1] - v[0];
        // invariant: f(low+len) = 0, f(low) = 1
        while (len > 1) {
            // cout << low << " " << len << ", ";
            int step = len / 2;
            int x = low + step;
            int c = 1;
            int p = 0;
            for (int i = 1; i < n; i++) {
                if (v[i] - v[p] < x) continue;
                p = i;
                c++;
            }
            bool possible = c >= m;
            if (possible) {
                low += step;
                len -= step;
            } else {
                len = step;
            }
        }
        cout << low << "\n";
    }
}