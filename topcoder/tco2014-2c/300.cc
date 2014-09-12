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

class SubstringReversal {
public:
  vector <int> solve(string s) {
    string c = s;
    sort(c.begin(), c.end());

    vi result({0, 0});
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == c[i]) continue;
      vector<string> possible;
      string r = s;
      reverse(r.begin(), r.end());
      for (int j = 0; j < r.size(); j++) {
        if (r[j] == c[i]) possible.push_back(r.substr(j));
      }
      sort(possible.begin(), possible.end());
      result[0] = i;
      result[1] = possible[0].size() - 1;
      break;
    }
    return result;
  }
};

int main() {
  SubstringReversal r;
  vi a;
  a = r.solve("zaacabaa");
  cout << a[0] << " " << a[1];
}
