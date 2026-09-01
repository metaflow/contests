// 1 ≤ m ≤ n ≤ 1'000'000'000, n-m ≤ 100000
// sqrt(1e9) = 31622+

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
    vector<bool> sieve(32000);
    vector<int> prime; // except 2 that is treated separately.
    // vector<int> prime2; // except 2 that is treated separately.
    for (int i = 3; i < sieve.size(); i += 2) {
        if (sieve[i/2]) continue;
        prime.push_back(i);
        for (int j = i * i; j < sieve.size(); j += i) {
            sieve[i] = false;
        }
    }
    int tc; cin >> tc;
    while (tc--) {        
        int a, b; cin >> a >> b;
        if (a == 1) a = 2;
        if (a <= 2 && 2 <= b) cout << 2 << endl;
        for (int x = a | 0b1; x <= b; x += 2) {
            bool b = true;
            for (int j = 0; j < prime.size(); j++) {
                int p = prime[j];
                if (x % p == 0) {
                    if (x != p) b = false;
                    break;
                }
                if (x < p * p) break;
            }
            if (b) cout << x << endl;
        }
        if (tc) cout << endl;
    }
}