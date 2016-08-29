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
  string s;
  getline(cin, s);
  while (tcc--) {
    getline(cin, s);
    vi prev(s.size() + 1, 0), current(s.size() + 1, 0);
    for (int i = 0; i < s.size(); i++) {
      prev.swap(current);
      current.assign(s.size() + 1, 0);
      for (int j = 0; j < s.size(); j++) {
        if (s[i] == s[s.size() - j - 1]) {
          current[j + 1] = prev[j] + 1;
        } else {
          current[j + 1] = max(current[j], prev[j + 1]);
        }
      }
    }
    cout << current[s.size()] << endl;
  }
}
