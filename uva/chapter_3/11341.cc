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

const int MAX = 100;
const int INF = 1000000;

int main() {
    int v[MAX], maxv[MAX + 1];
    int tcc;
    cin >> tcc;
    while (tcc--) {
        int n, m;
        cin >> n >> m;
        fill_n(maxv, MAX + 1, 0);
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < m; i++) cin >> v[i];
            for (int j = MAX; j >= 0; j--) {
                int &t = maxv[j];
                t = -INF;
                for (int i = 0; i < m; i++) {
                    if (v[i] < 5) continue;
                    if (j - i - 1 < 0) break;
                    t = max(t, maxv[j - i - 1] + v[i]);
                }
            }
        }
        if (maxv[m] < 0) {
            cout << "Peter, you shouldn't have played billiard that much."
                 << endl;
        } else {
            cout << "Maximal possible average mark - "
            << setprecision(2) << fixed << ((double)maxv[m] / n + 1e-9)
            << "." << endl;
        }
    }
}
