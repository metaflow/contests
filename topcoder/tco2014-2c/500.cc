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
const int MAX = 2500;

int w[MAX][MAX];

class CliqueGraph {
public:
  long long calcSum(int N, vector <int> V, vector <int> sizes) {
    fill(&w[0][0], &w[MAX][0], 2 * MAX);
    int f = 0;
    int t = 0;
    for (auto s : sizes) {
      f = t;
      t += s;
      for (int i = f; i < t; ++i)
        for (int j = i + 1; j < t; ++j){
          w[V[i]][V[j]] = 1;
          w[V[j]][V[i]] = 1;
        }
    }
    for (int k = 0; k < N; ++k)
    for (int i = 0; i < N; ++i)
    for (int j = i + 1; j < N; ++j)
      w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
    long long result = 0;
    for (int i = 0; i < N; ++i)
    for (int j = i + 1; j < N; ++j)
      result += w[i][j];
    return result;
  }
};

int main() {
  CliqueGraph cg;
  cerr << cg.calcSum(4, {0,1,2,0,3}, {3,2}) << endl;
  cerr << cg.calcSum(5, {0,1,2,3,1,2,4}, {4,3}) << endl;
  cerr << cg.calcSum(15,
{1,3,5,7,9,11,13,0
,2,3,6,7,10,11,14,0
,4,5,6,7,12,13,14,0
,8,9,10,11,12,13,14,0},
{8,8,8,8}) << endl;
}
