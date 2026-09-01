#include <math.h>
#include <algorithm>
#include <bitset>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    string s;
    while (true) {
        cin >> s;
        if (s[0] == '0') break;
        long long c1, c2, w;
        c1 = 1;
        c2 = 0;
        w = 0;
        for (int i = s.size() - 1; i >= 0; i--) {
            int x = s[i] - '0';
            long long t = 0;
            if (x >= 1 && x <= 9) t += c1;
            w = (w / 10) + x * 10;
            if (w >= 10 && w <= 26) t += c2;
            c2 = c1;
            c1 = t;
        }
        cout << c1 << endl;
    }
}