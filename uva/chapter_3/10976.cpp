#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

using ul = unsigned long long;

int main() {
    int k;
    while (scanf("%d", &k) == 1) {
        ul x;
        x = 2 * k - 1;
        vector<pair<ul, ul> > v;
        for (ul y = k + 1; y <= 2 * k; y++) {
            ul x = k * y / (y - k);
            if (x * y != k * (x + y)) continue;
            v.push_back(make_pair(x, y));
        }
        // reverse(v.begin(), v.end());
        printf("%lu\n", v.size());
        for (auto p : v) {
            printf("1/%d = 1/%llu + 1/%llu\n", k, p.first, p.second);
        }
    }
    return 0;
}

