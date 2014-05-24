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

int main() {
    int n;
    cin >> n;
    int a = 0, b = 0;
    for (int i = 0; i < n; i ++) {
        int v;
        cin >> v;
        if (v == 100) {
            a++;
        } else {
            b++;
        }
    }
    b %= 2;
    if (b) a -= 2;
    if (a >= 0 && a % 2 == 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
