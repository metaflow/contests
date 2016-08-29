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

const int MAX = 100;

int main() {
    bool a[MAX], b[MAX];
    int tcc;
    cin >> tcc;
    while (tcc--) {
        fill_n(a, MAX, false);
        int n, k, v;
        cin >> n >> k >> v;
        n--;
        v = (v % k + k) % k;
        a[v] = true;
        while (n--) {
            cin >> v;
            v = v % k;
            fill_n(b, MAX, false);
            for (int i = 0; i < k; i++) {
                if (!a[i]) continue;
                b[(i + v + k) % k] = true;
                b[(i - v + k) % k] = true;
            }
            copy_n(b, MAX, a);
        }
        if (a[0]) {
            cout << "Divisible" << endl;
        } else {
            cout << "Not divisible" << endl;
        }
    }
}
