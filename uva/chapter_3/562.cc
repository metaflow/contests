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

const int MAX = 50001;
const int MAX_N = 101;

int memo[MAX_N][MAX];
int values[MAX_N];

int diff(int n, int s1, int s2) {
    if (n < 0) return abs(s1 - s2);
    int &v = memo[n][s1];
    if (v == -1) {
        v = diff(n - 1, s1 + values[n], s2);
        v = min(v, diff(n - 1, s1, s2 + values[n]));
    }
    return v;
}

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        int n;
        cin >> n;
        fill(&memo[0][0], &memo[MAX_N][0], -1);
        for (int i = 0; i < n; i++) {
            cin >> values[i];
        }
        cout << diff(n - 1, 0, 0) << endl;
    }
}
