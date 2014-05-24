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
using ll = long long;

int main() {
    int n;
    cin >> n;
    n++;
    vector<ll> a(n);
    a[0] = 0;
    for (int i = 1; i < n; i++) cin >> a[i];
    vector<ll> b(a);
    sort(b.begin(), b.end());
    for (int i = 1; i < n; i++) {
        a[i] += a[i - 1];
        b[i] += b[i - 1];
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            cout << (a[r] - a[l - 1]) << endl;
        } else {
            cout << (b[r] - b[l - 1]) << endl;
        }
    }
}
