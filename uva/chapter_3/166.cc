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

const int INF = 10000;
const int MAX = 700 / 5;

int main() {
    int coins[] = { 5, 10, 20, 50, 100, 200 };
    for (auto &c : coins) c /= 5;
    int min_ways[MAX + 1];
    fill_n(min_ways, MAX + 1, INF);
    min_ways[0] = 0;
    for (auto c : coins) {
        for (int s = c; s <= MAX; s++) {
            min_ways[s] = min(min_ways[s], min_ways[s - c] + 1);
        }
    }
    int counts[6];
    int possible[MAX + 1];
    while (true) {
        fill_n(possible, MAX + 1, INF);
        possible[0] = 0;
        int total = 0;
        for (auto &c : coins) {
            int count;
            cin >> count;
            count = min(count, 100);
            total += count;
            while (count--) {
                for (int s = MAX; s - c >= 0; s--) {
                    possible[s] = min(possible[s], possible[s - c] + 1);
                }
            }
        }
        if (total == 0) break;
        double d;
        cin >> d;
        int amount = int(round(d * 100 / 5));
        int r = INF;
        for (int s = amount; s <= amount + 200/5; s++) {
            r = min(r, possible[s] + min_ways[s - amount]);
        }
        cout << setw(3) << r << endl;
    }
}
