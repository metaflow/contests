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
    int m, n, t;
    while (cin >> m >> n >> t) {
        if (m > n) swap(m, n); // n >= m
        int min_beer = t + 1;
        int best = 0;
        for (int i = 0; i <= t/n; i++) {
            int j = (t - i * n) / m;
            int beer = t - i * n - j * m;
            if (beer < min_beer) {
                best = i + j;
                min_beer = beer;
                if (min_beer == 0) break;
            }
        }
        cout << best;
        if (min_beer) cout << " " << min_beer;
        cout << endl;
    }
}
