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

vector<int> height, width;

int lis() {
    vector<int> w(height.size(), 0);
    int lis = 0;
    for (int i = 0; i < height.size(); i++) {
        int best = 0;
        for (int j = 0; j < i; j++) {
            if (height[i] > height[j] && w[j] > best) best = w[j];
        }
        w[i] = best + width[i];
        lis = max(lis, w[i]);
    }
    return lis;
}

int main() {
    int tcc;
    cin >> tcc;
    for (int tc = 1; tc <= tcc; tc++) {
        int n;
        cin >> n;
        height.resize(n);
        width.resize(n);
        for (int i = 0; i < n; i++) cin >> height[i];
        for (int i = 0; i < n; i++) cin >> width[i];
        int i = lis();
        reverse(height.begin(), height.end());
        reverse(width.begin(), width.end());
        int d = lis();
        if (i >= d) {
            printf("Case %d. Increasing (%d). Decreasing (%d).\n", tc, i, d);
        } else {
            printf("Case %d. Decreasing (%d). Increasing (%d).\n", tc, d, i);
        }
    }
}
