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

const int MAX = 10000;

int main() {
    vi coins;
    for (int i = 1; i <= 21; i++) coins.push_back(i * i * i);
    llu ways[MAX + 1];
    fill_n(ways, MAX + 1, 0);
    ways[0] = 1;
    for (auto c : coins)
    for (int sum = c; sum <= MAX; sum++) ways[sum] += ways[sum - c];
    int amount;
    while (cin >> amount) cout << ways[amount] << endl;
}
