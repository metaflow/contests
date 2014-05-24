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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> C(n);
    vector<int> V(m);
    vector<ll> S(n);
    int prev = -1;
    for (int i = 0; i < m; i++) {
        int v;
        cin >> v;
        v--;
        V[i] = v;
        if (prev != -1 && prev != v) {
            C[v].push_back(prev);
            C[prev].push_back(v);
        }
        prev = v;
    }
    V.insert(V.begin(), V[1]);
    V.push_back(V[V.size() - 2]);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        S[i] = 0;
        for (auto v : C[i]) {
            S[i] += abs(i - v);
        }
        sum += S[i];
    }
    sum /= 2;
    ll best = 0;
    for (int i = 1; i <= m; i++) {
        int x = V[i];
        if ((x > V[i - 1] && x > V[i + 1]) ||
            (x < V[i - 1] && x < V[i + 1])) {
            int v = V[i - 1];
            ll t = 0;
            for (auto j : C[x]) {
                t += abs(j - v);
            }
            t -= S[x];
            best = min(best, t);
            v = V[i + 1];
            t = 0;
            for (auto j : C[x]) {
                t += abs(j - v);
            }
            t -= S[x];
            best = min(best, t);
        }
    }
    cout << sum + best << endl;
}
