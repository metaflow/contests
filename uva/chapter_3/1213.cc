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

const int MAX_N = 1121;
const int MAX_K = 15;
int memo[MAX_N][MAX_K][200];
vi primes;

void prepare_primes() {
    bitset<MAX_N> b;
    for (int i = 2; i < MAX_N; i++) {
        if (b[i]) continue;
        primes.push_back(i);
        for (int j = i; j < MAX_N; j += i) b[j] = true;
    }
}

int count(int n, int k, int pi) {
    if (k == 0) {
        if (n == 0) return 1;
        return 0;
    }
    if (n == 0) return 0;
    int &v = memo[n][k][pi];
    if (v == -1) {
        v = 0;
        // cerr << n << " " << k << " " << pi << endl;
        for (int i = pi; i < primes.size(); i++) {
            if (primes[i] > n) break;
            v += count(n - primes[i], k - 1, i + 1);
        }
    }
    return v;
}

int main() {
    int n, k;
    prepare_primes();
    fill(&memo[0][0][0], &memo[MAX_N][0][0], -1);
    while (cin >> n >> k, n) {
        cout << count(n, k, 0) << endl;
    }
}
