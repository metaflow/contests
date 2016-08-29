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

const int MAX = 201;

bool next(int &v) {
    char s[10];
    int i = 0;
    while (true) {
        char c = getchar();
        if (c >= '0' && c <= '9') {
            s[i] = c;
            i++;
        } else {
            if (i) {
                s[i] = '\0';
                v = atoi(s);
                return c == ' ';
            }
            if (c == ' ') continue;
            return false;
        }
    }
    return false;
}



int main() {
    int tcc;
    next(tcc);
    while (tcc--) {
        bitset<MAX> b;
        int sum = 0;
        int v;
        while (true) {
            bool f = next(v);
            for (int i = MAX - 1; i > v; i--) {
                b[i] = b[i] || b[i - v];
            }
            b[v] = true;
            sum += v;
            if (!f) break;
        }
        if (b[sum / 2] && sum % 2 == 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
