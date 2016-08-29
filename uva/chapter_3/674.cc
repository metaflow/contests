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

const int MAX = 7489;

int main() {
    int coins[] = {50, 25, 10, 5, 1};
    int ways[MAX + 1];
    fill_n(ways, MAX + 1, 0);
    ways[0] = 1;
    for (auto c : coins) {
        for (int i = MAX; i >= 0; i--)
        for (int j = c; i - j >= 0; j += c)
            ways[i] += ways[i - j];
    }
    int a;
    while (cin >> a) {
        cout << ways[a] << endl;
    }
}
