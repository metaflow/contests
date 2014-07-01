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

const int MAX = 50;

class FixedDiceGameDiv1 {
public:
  double getExpectation(int a, int b, int c, int d) {
    double ca[2501], cb[2501], r[2501];
    fill_n(ca, 2501, 0);
    fill_n(cb, 2501, 0);
    fill_n(r, 2501, 0);
    ca[0] = 1;
    cb[0] = 1;
    for (int i = 0; i < a; i++) {
      for (int j = 2500; j >= 0; j--) {
        if (ca[j] == 0) continue;
        for (int k = 1; k <= b; k++) ca[j + k] += ca[j];
        ca[j] = 0;
      }
    }
    double total = 0;
    for (int j = 2500; j > 0; j--) total += ca[j];
    for (int j = 2500; j > 0; j--) ca[j] /= total;

    for (int i = 0; i < c; i++) {
      for (int j = 2500; j >= 0; j--) {
        if (cb[j] == 0) continue;
        for (int k = 1; k <= d; k++) cb[j + k] += cb[j];
        cb[j] = 0;
      }
    }
    total = 0;
    for (int j = 2500; j > 0; j--) total += cb[j];
    for (int j = 2500; j > 0; j--) cb[j] /= total;
    for (int j = 2; j <= 2500; j++) cb[j] += cb[j-1];

    // for (int j = 1; j <= 2500 && cb[j - 1] != 1; j++)
    //     cerr << j + 1 << " " << cb[j] << " " << ca[j + 1] << endl;

    double result = 0;
    total = 0;
    for (int j = 2; j <= 2500; j++) {
      result += cb[j - 1] * ca[j] * j;
      total += cb[j - 1] * ca[j];
    }
    cerr << total << endl;
    if (total < 1e-100) return -1;
    return result / total;
  }
};

int main() {
  FixedDiceGameDiv1 g;
  // cout << g.getExpectation(1, 2, 1, 5) << endl;
  // cout << g.getExpectation(3, 1, 1, 3) << endl;
  // cout << g.getExpectation(1, 5, 1, 1) << endl;
  // cout << g.getExpectation(2, 6, 50, 30) << endl;
  cout << g.getExpectation(50, 11, 50, 50) << endl;
}

