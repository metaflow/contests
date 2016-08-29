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

const int MAX = 101;

int main() {
    int n;
    int a[MAX][MAX];
    while (cin >> n, n) {
        fill(&a[0][0], &a[MAX][0], 0);
        while (n--) {
            int x, y;
            cin >> x >> y;
            a[x][y]++;
        }
        for (int x = 1; x < MAX; x++)
        for (int y = 1; y < MAX; y++) {
            a[x][y] += max(a[x - 1][y], a[x][y - 1]);
        }
        cout << a[MAX - 1][MAX - 1] << endl;
    }
    cout << "*" << endl;
}
