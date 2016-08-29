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
    int tcc;
    cin >> tcc;
    for (int tc = 1; tc <= tcc; tc++) {
        int n;
        cin >> n;
        n--;
        int best_sum = 0;
        int best_start = 1;
        int best_end = 0;
        int sum = 0;
        int start = 1;
        int end;
        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            sum += v;
            end = i + 2;
            if (sum > best_sum ||
                 (sum == best_sum &&
                 (best_end - best_start) < (end - start))) {
                best_sum = sum;
                best_start = start;
                best_end = end;
            }
            if (sum < 0) {
                sum = 0;
                start = end;
            }
        }
        if (best_sum > 0) {
            printf("The nicest part of route %d is between stops %d and %d\n",
                tc, best_start, best_end);
        } else {
            printf("Route %d has no nice parts\n", tc);
        }
    }
}
