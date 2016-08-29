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

map<string, int> memo;

int collapsable(string s) {
    if (memo.count(s)) return memo[s];
    int r = 0;
    unsigned i = 0;
    while (i < s.size()) {
        unsigned j = i + 1;
        while (j < s.size() && s[i] == s[j]) j++;
        if (j - i > 1) {
            r = collapsable(s.substr(0, i) + s.substr(j));
            if (r) break;
        }
        i = j;
    }
    memo[s] = r;
    return r;
}

int main() {
    memo[""] = 1;
    int tcc;
    cin >> tcc;
    string s;
    while (tcc--) {
        cin >> s;
        cout << collapsable(s) << endl;
    }
}
