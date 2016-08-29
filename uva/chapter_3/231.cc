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
    int tcc = 0;
    int v;
    vector<int> lic;
    while (cin >> v, v != -1) {
        if (tcc) printf("\n");
        tcc++;
        lic.clear();
        lic.push_back(-v);
        while (cin >> v, v != -1) {
            v = -v;
            auto it = upper_bound(lic.begin(), lic.end(), v);
            if (it == lic.end()) {
                lic.push_back(v);
                continue;
            }
            *it = v;
        }
        printf("Test #%d:\n  maximum possible interceptions: %llu\n",
            tcc, (unsigned long long)(lic.size()));
    }
}
