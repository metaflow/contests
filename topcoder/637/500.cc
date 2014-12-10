#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

class PathGame {
public:
  string judge(vector <string> board) {
    string a = board[0]; string b = board[1];
    int left = 0;
    bool win = false;
    for (int i = 0; i < a.size(); i++) {
      if (a[i] == b[i]) continue;
      if (left - i != 0) {
        if (a[left] != a[i]) {
          if (left - i % 2 == 0) win = !win;
        } else {
          if (left - i % 2 == 1) win = !win;
        }
      }
      left = i + 1;
    }
    if (a.size() - left % 2 == 0) win = !win;
    return "";
  }

};

int main() {

}
