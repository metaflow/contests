#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  string s;
  while (getline(cin, s)) {
    stringstream ss(s);
    int x; ss >> x;
    getline(cin, s);
    ss.str(s); ss.clear();
    vi a;
    int i;
    while (ss >> i) a.emplace_back(i);
    a.pop_back();
    int r = 0; int m = a.size();
    for (auto k : a) {
      r = r * x + k * m;
      m--;
    }
    cout << r << endl;
  }
}
