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
    int tcc = 1000;
    cout << tcc << endl;
    srand(time(NULL));
    while (tcc--) {
        int m = range(1,20000);
        cout << m << endl;
        while (m--) {
            cout << range(1,10000) << " " << range(1,10000) << " ";
        }
        cout << endl;
    }
}
