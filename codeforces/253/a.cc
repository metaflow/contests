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
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

const int MAX = 5;

int main() {
    int w[MAX][MAX];
    string l = "RGBYW";
    fill(&w[0][0], &w[MAX][0], 0);

    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        int r = l.find(s[0]);
        int c = s[1] - '1';
        if (w[r][c]) continue;
        w[r][c] = 1;
    }

    bool f[1 << (2 * MAX)];

    int a = 20;
    for (int i = 0; i < (1 << MAX); i++) {
        for (int j = 0; j < (1 << MAX); j++) {
            fill_n(f, 1 << (2 * MAX), false);
            bool ok = true;
            for (int r = 0; r < MAX; r++) {
                for (int c = 0; c < MAX; c++) {
                    if (w[r][c] == 0) continue;
                    int k = (i & (1 << r)) + ((j & (1 << c)) << MAX);
                    //cerr << k << endl;
                    if (f[k]) {
                        ok = false;
                        break;
                    }
                    f[k] = true;
                }
            }
            if (!ok) continue;
            int bits = 0;
            for (int k = 0; k < MAX; k++) if (i & (1 << k)) bits++;
            for (int k = 0; k < MAX; k++) if (j & (1 << k)) bits++;
            a = min(a, bits);
        }
    }

    cout << a << endl;
}

