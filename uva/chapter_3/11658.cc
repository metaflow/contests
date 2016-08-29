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

int main() {
    int n, x;
    bitset<10001> b;
    while (cin >> n >> x, n) {
        b.reset();
        b[0] = true;
        int a;
        for (int i = 1; i <= n; i++) {
            double d;
            cin >> d;
            int v = round(d * 100);
            if (i == x) {
                a = v;
                continue;
            }
            for (int j = 10000; j >= v; j--) {
                b[j] = b[j] || b[j - v];
            }
        }
        int r = max(0, 5001 - a);
        while (!b[r]) r++;
        cout << fixed << setprecision(2)
        << round(double(10000 * a) / (r + a)) / 100 << endl;
    }
}
