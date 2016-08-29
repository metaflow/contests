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

const int INF = 100000;

int k, s;
int memo[301][301][40];
int A[40], B[40];

int find(int a, int b, int x) {
    if (a*a + b*b == s) return 0;
    if (a*a + b*b > s || x < 0) return INF;
    int &v = memo[a][b][x];
    if (v == 0) v = min(find(a, b, x - 1), 1 + find(a + A[x], b + B[x], x));
    return v;
}

int main() {
    int n;
    cin >> n;
    while(n--) {
        cin >> k >> s;
        s = s*s;
        fill(&memo[0][0][0], &memo[301][0][0], 0);
        for (int i = 0; i < k; i++) {
            cin >> A[i] >> B[i];
        }
        int r = find(0, 0, k - 1);
        if (r == INF) {
            cout << "not possible" << endl;
        } else {
            cout << r << endl;
        }
    }
}
