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

const int INF = 100000;
const int MAX = 1001;

int main() {
    int mw[MAX], load[MAX], weight[MAX];
    int n;
    while (cin >> n, n) {
        for (int i = n - 1; i >= 0; i--) {
            cin >> weight[i] >> load[i];
        }
        fill_n(mw, MAX, INF);
        mw[0] = 0;
        for (int j = 0; j < n; j++)
        for (int i = MAX - 2; i >= 0; i--) {
            if (load[j] < mw[i]) continue;
            mw[i + 1] = min(mw[i + 1], weight[j] + mw[i]);
        }
        int r = MAX - 1;
        while (mw[r] == INF) r--;
        cout << r << endl;
    }
}
