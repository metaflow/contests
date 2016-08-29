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

using llu = unsigned long long;

int coins[] = {1, 5, 10, 25, 50};
llu memo[30001][5];

llu count(int sum, int from_coin) {
    if (sum == 0) return 1;
    if (from_coin < 0 || sum < 0) return 0;
    llu &v = memo[sum][from_coin];
    if (v == 0) {
        v = count(sum - coins[from_coin], from_coin) + count(sum, from_coin - 1);
    }
    return v;
}

int main() {
    int n;
    while (cin >> n) {
        llu c = count(n, 4);
        if (c == 1) {
            printf("There is only 1 way to produce %d cents change.\n", n);
        } else {
            printf("There are %llu ways to produce %d cents change.\n", c, n);
        }
    }
}
