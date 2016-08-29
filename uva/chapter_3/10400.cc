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

const int MAX_V = 32000;
const int MIN_V = -32000;
const int MAX_N = 100;
char memo[MAX_V - MIN_V + 1][MAX_N];
int value[MAX_N];

char build(int target, int k) {
    if (k < 0 || target < MIN_V || target > MAX_V) return 'N';
    char &a = memo[target - MIN_V][k];
    if (a == ' ') {
        a = 'N';
        int v = value[k];
        if (build(target + v, k - 1) != 'N') {
            a = '-';
            return a;
        }
        if (build(target - v, k - 1) != 'N') {
            a = '+';
            return a;
        }
        if (v != 0 && build(target * v, k - 1) != 'N') {
            a = '/';
            return a;
        }
        if (v == 0 && target == 0) {
            for (int i = MIN_V; i <= MAX_V; i++) {
                if (build(i, k - 1) == 'N') continue;
                a = '*';
                return a;
            }
        }
        if (v != 0 && target % v == 0 && build(target / v, k - 1) != 'N') {
            a = '*';
            return a;
        }
    }
    return a;
}

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        fill(&memo[0][0], &memo[MAX_V - MIN_V + 1][0], ' ');
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) cin >> value[i];
        memo[value[0] - MIN_V][0] = 'Y';
        int target;
        cin >> target;
        if (build(target, n - 1) == 'N') {
            cout << "NO EXPRESSION" << endl;
        } else {
            string s = "=" + to_string(target);
            int t = target;
            bool any = false;
            for (int k = n - 1; k >= 0; k--) {
                int v = value[k];
                s = to_string(v) + s;
                if (k == 0) break;
                if (any) {
                    s = '+' + s;
                } else {
                    s = build(t, k) + s;
                    switch (build(t, k)) {
                        case '+': t -= v; break;
                        case '-': t += v; break;
                        case '/': t *= v; break;
                        case '*': if (v == 0) {
                                    for (int i = MIN_V; i <= MAX_V; i++) {
                                        if (build(i, k - 1) == 'N') continue;
                                        t = i;
                                        break;
                                    }
                                    break;
                                  }
                                  t /= v;
                                  break;
                    }
                }
            }
            cout << s << endl;
        }
    }
}
