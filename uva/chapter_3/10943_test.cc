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
    srand (time(NULL));
    for (int i = 0; i < 100; i++) {
        cout << range(1, 100) << " " << range(1, 100) << endl;
    }
    cout << "0 0";
}
