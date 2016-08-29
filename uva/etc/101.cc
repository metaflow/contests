#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  int n;
  cin >> n;
  vector<stack<int>> piles(n);
  vector<int> pos(n);
  for (int i = 0; i < n; i++) {
    piles[i].push(i);
    pos[i] = i;
  }
  string opa;
  while (cin >> opa) {
    if (opa == "quit") break;
    stack<int> move;
    int a, b;
    string opb;
    cin >> a >> opb >> b;
    if (pos[a] == pos[b]) continue;
    if (opa == "move") {
      while (true) {
        int t = piles[pos[a]].top();
        if (t == a) break;
        piles[pos[a]].pop();
        piles[t].push(t);
        pos[t] = t;
      }
    }
    while (true) {
      int t = piles[pos[a]].top();
      piles[pos[a]].pop();
      move.push(t);
      if (t == a) break;
    }
    if (opb == "onto") {
      while (true) {
        int t = piles[pos[b]].top();
        if (t == b) break;
        piles[pos[b]].pop();
        piles[t].push(t);
        pos[t] = t;
      }
    }
    while (!move.empty()) {
      int t = move.top(); move.pop();
      pos[t] = pos[b];
      piles[pos[b]].push(t);
    }
  }
  for (int i = 0; i < n; i++) {
    printf("%d:", i);
    stack<int> s;
    while (!piles[i].empty()) {
      s.push(piles[i].top()); piles[i].pop();
    }
    while (!s.empty()) {
      printf(" %d", s.top()); s.pop();
    }
    printf("\n");
  }
}
