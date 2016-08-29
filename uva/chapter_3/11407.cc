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

const int MAX = 10000;

int main() {
    int count[MAX + 1];
    fill_n(count, MAX + 1, 2 * MAX);
    count[0] = 0;
    for (int i = 1; i <= sqrt(MAX); ++i) {
        int t = i * i;
        for (int j = t; j <= MAX; ++j) {
            count[j] = min(count[j], count[j - t] + 1);
        }
    }
    int tcc;
    scanf("%d", &tcc);
    while (tcc--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", count[n]);
    }
}

