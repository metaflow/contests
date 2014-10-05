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
#include <queue>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;

int main() {
  int n;
  while (cin >> n) {
    string o = "+------------------------+\n|{0}.{4}.{7}.{10}.{13}.{16}.{19}.{22}.{25}.{28}.{31}.|D|)\n|{1}.{5}.{8}.{11}.{14}.{17}.{20}.{23}.{26}.{29}.{32}.|.|\n|{2}.......................|\n|{3}.{6}.{9}.{12}.{15}.{18}.{21}.{24}.{27}.{30}.{33}.|.|)\n+------------------------+";
    for (int i = 0; i < 34; i++) {
      char buffer[33];
      sprintf(buffer, "%d", i);
      string t = "{";
      t = t + buffer + "}";
      o = o.replace(o.find(t), t.size(), (n > i ? "O" : "#"));
    }
    cout << o << endl;
  }
}
