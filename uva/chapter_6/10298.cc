#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 1000001;

int main() {
  string s;
  int p[MAX];
  while (cin >> s, s != ".") {
    int j = -1;
    p[0] = - 1;
    for (int i = 0; i < s.size(); i++) {
      while (j >= 0 && s[j] != s[i]) j = p[j];
      j++;
      p[i + 1] = j;
    }
    int w = s.size() - p[s.size()];
    if (s.size() % w != 0) w = s.size();
    cout << s.size() / w << endl;
  }
}
