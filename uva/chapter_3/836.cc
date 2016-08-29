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
const int MAX = 26;

int main() {
    int tcc;
    cin >> tcc;
    int m[MAX][MAX];
    fill(&m[0][0], &m[MAX][0], 0);
    while (tcc--) {
        string s;
        cin >> s;
        int n = s.size();

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                m[i][j] = (s[j - 1] == '1') ? 1 : 0;
                m[i][j] += m[i - 1][j] + m[i][j - 1] - m[i - 1][j - 1];
            }
            if (i != n) cin >> s;
        }

        int best = 0;
        for (int l = 0; l < n; l++)
        for (int b = 0; b < n; b++)
        for (int r = l + 1; r <= n; r++)
        for (int t = b + 1; t <= n; t++) {
            int v = (r - l) * (t - b);
            if (v <= best) continue;
            if (m[r][t] - m[r][b] - m[l][t] + m[l][b] != v) continue;
            best = v;
        }
        cout << best << endl;
        if (tcc) cout << endl;
    }
}
