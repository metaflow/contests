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
    int a[4];
    for (int i = 0; i < 4; i++) cin >> a[i];
    string s;
    cin >> s;

    int result = 0;
    for (int i = 0; i < s.size(); i++) {
        result += a[(s[i] - '1')];
    }
    cout << result << endl;
}
