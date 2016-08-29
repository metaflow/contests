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

int range(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main() {
    srand(time(NULL));
    int tcc = 100;
    cout << tcc << endl;
    while (tcc--) {
        int n = range(1, 10);
        int m = range(1, 100);
        cout << n << " " << m << endl;
        for (int i = 0; i < n; i++) {
            int v = 1;
            for (int j = 0; j < m; j++) {
                v = min(10, v + range(0, 9));
                cout << v << " ";
            }
            cout << endl;
        }
    }
}
