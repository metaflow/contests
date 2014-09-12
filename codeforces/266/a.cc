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
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    int result = a * n;
    int k = n / m;
    int d = n % m;
    result = min(result, k * b + d * a);
    result = min(result, (k + 1) * b);
    cout << result << endl;
}
