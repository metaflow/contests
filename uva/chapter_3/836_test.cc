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

int range(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main() {
    int tcc = 1000;
    for (int tc = 0; tc < tcc; tc++) {
        int n = range(1, 25);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cout << range(0, 1);
            cout << endl;
        }
        cout << endl;
    }
}
