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

struct tube {
    ll v, t;
};

struct {
    bool operator()(tube* a, tube* b)
    {
        return a->v < b->v;
    }
} customLess;

int main() {
    int n, q;
    cin >> n >> q;
    vector<tube*> tubes;
    vector<tube*> sorted_tubes;
    bool sorted = false;
    for (int i = 0; i < n; i++) {
        ll v;
        cin >> v;
        tubes.push_back(new tube());
        tubes.back()->v = v;
        sorted_tubes.push_back(tubes.back());
    }
    tubes.push_back(new tube());
    tubes.back()->v = 10000000000000000; // 1e16
    sorted_tubes.push_back(tubes.back());
    int upto = 0;
    for (int qq = 0; qq < q; qq++) {
        int t;
        cin >> t;
        if (t == 1) {
            ll p, x;
            cin >> p >> x;
            sorted = false;
            tubes[p - 1]->v = x;
        } else {
            ll v;
            cin >> v;
            if (!sorted) {
                sort(sorted_tubes.begin(), sorted_tubes.end(), customLess);
                upto = 0;
                sorted_tubes[0]->t = 0;
                sorted = true;
            }
            while (v > sorted_tubes[upto]->t) {
                upto++;
                sorted_tubes[upto]->t = sorted_tubes[upto - 1]->t
                    + upto * (sorted_tubes[upto]->v - sorted_tubes[upto - 1]->v);
            }

            int i;
            for (i = 0; i <= upto; i++) {
                if (v <= sorted_tubes[i]->t) break;
            }
            ll delta = v - sorted_tubes[i - 1]->t;
            double relation = (1.0 * delta / i) + sorted_tubes[i - 1]->v;
            printf("%.5f\n", relation);
        }
    }
}
