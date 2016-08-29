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
    int m, n;
    int best[10201];
    // int count = 0;
    while (cin >> m >> n) {
        // count++;
        // cerr << count << " " << m << " " << n << endl;
        fill(&best[0], &best[10201], -1);
        best[0] = 0;
        for (int i = 0; i < n; i++) {
            int p;
            int v;
            cin >> p >> v;
            for (int j = m + 200 - p; j >= 0; j--) {
                if (best[j] == -1) continue;
                best[j + p] = max(best[j + p], best[j] + v);
            }
        }
        int answer = 0;
        for (int i = 0; i <= m + 200; i++) {
            if (i <= 2000 && i > m) continue;
            answer = max(answer, best[i]);
        }
        cout << answer << endl;
    }
}
