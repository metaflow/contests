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

const int MAX = 20002;

int main() {
    int tcc;
    cin >> tcc;
    int counts[MAX];
    while (tcc--) {
        int n;
        cin >> n;
        vector<ii> dolls;
        while (n--) {
            ii d;
            cin >> d.first >> d.second;
            d.second = -d.second;
            dolls.push_back(d);
        }
        sort(dolls.begin(), dolls.end());
        fill(counts, counts + MAX, 0);
        vi lis;
        for (auto d : dolls) {
            auto it = upper_bound(lis.begin(), lis.end(), d.second);
            if (it == lis.end()) {
                lis.push_back(d.second);
            } else {
                *it = d.second;
            }
        }
        cout << lis.size() << endl;
    }
}
