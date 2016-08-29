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

const int MAX = 30;

int main() {
    int n;
    cin >> n;
    int order[MAX];
    int v;
    for (int i = 0; i < n; i++) {
        cin >> v;
        order[i] = v - 1;
    }
    int lengths[MAX];
    int data[MAX];
    while (cin >> v) {
        data[v - 1] = order[0];
        for (int i = 1; i < n; i++) {
            cin >> v;
            data[v - 1] = order[i];
        }
        int best = 1;
        for (int i = 0; i < n; i++) {
            int t = 0;
            for (int j = 0; j < i; j++) {
                if (data[i] > data[j]) t = max(t, lengths[j]);
            }
            lengths[i] = t + 1;
            best = max(best, lengths[i]);
        }

        cout << best << endl;
    }
}
