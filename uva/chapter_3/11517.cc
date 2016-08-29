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

using pii = pair<int, int>;

const int INF = 100000;

int coins[100];
pii memo[100][10001];

pii find(int sum, int k) {
    if (sum <= 0) return make_pair(0, 0);
    if (k < 0) return make_pair(INF, INF);
    pii &v = memo[k][sum];
    if (v.first == 0) {
        v = find(sum - coins[k], k - 1);
        v.first += coins[k];
        v.second++;
        v = min(v, find(sum, k - 1));
    }
    return v;
}

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        int sum, n;
        cin >> sum >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= sum; j++) {
                memo[i][j].first = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            cin >> coins[i];
        }
        pii r = find(sum, n - 1);
        printf("%d %d\n", r.first, r.second);
    }
}
