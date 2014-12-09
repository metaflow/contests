#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

void judge(vi &h, string &name, int time, int player, char color) {
  int t = h[player];
  if (t >= 2) return;
  t++;
  if (color == 'r') t++;
  if (t >= 2) {
    cout << name << " " << player << " " << time << endl;
  }
  h[player] = t;
}

int main() {
  string home, guest;
  cin >> home >> guest;
  vector<int> h(100, 0), g(100, 0);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int time, player;
    char team, color;
    cin >> time >> team >> player >> color;
    if (team == 'h') {
      judge(h, home, time, player, color);
    } else {
      judge(g, guest, time, player, color);
    }
  }
}
