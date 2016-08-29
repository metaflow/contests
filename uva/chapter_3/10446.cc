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

const int MAX = 62;

llu memo[MAX][MAX];

llu count(int n, unsigned int back) {
    if(n <= 1) return 1;
    llu &r = memo[n][back];
    if (r == 0) {
        r = 1;
        for (int i = 1; i <= back; i++) r += count(n-i, back);
    }
    return r;
}

int main() {
    int n, back;
    int tcc = 0;
    fill(&memo[0][0], &memo[MAX][0], 0);
    while (cin >> n >> back, n < 61) {
        tcc++;
        cout << "Case " << tcc << ": " << count(n, back) << endl;
    }
}
