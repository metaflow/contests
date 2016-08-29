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

const int MAX_W = 31;

int main() {
    int tcc;
    cin >> tcc;
    while (tcc--) {
        int n;
        cin >> n;
        vi W(MAX_W);
        while (n--) {
            int p, w;
            cin >> p >> w;
            for (int i = MAX_W - w - 1; i >= 0; i--) {
                W[i + w] = max(W[i + w], p + W[i]);
            }
        }
        int g;
        cin >> g;
        int sum = 0;
        while (g--) {
            int w;
            cin >> w;
            sum += W[w];
        }
        cout << sum << endl;
    }
}
