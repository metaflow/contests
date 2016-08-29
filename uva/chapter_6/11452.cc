#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int tcc;
  cin >> tcc;
  while (tcc--) {
    string s;
    cin >> s;
    int n = s.size();
    for (int k = n / 2; k > n / 3; k--) {
      if (s.find(s.substr(k, k)) != 0) continue;
      if (s.find(s.substr(2 * k, k)) != 0) continue;
      for (int i = 0; i < 8; i++) cout << s[(n + i) % k];
      cout << "..." << endl;
      break;
    }
  }
}
