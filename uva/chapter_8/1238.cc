#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();
const int MAX = 31;
const int MAX_SUM = 6000;

int sign[MAX], value[MAX];
bitset<MAX_SUM> possible;
bool checked[MAX][MAX][MAX_SUM];
int N;

void dp(int pos, int open_brackets, int sum) {
  if (checked[pos][open_brackets][sum]) return;
  checked[pos][open_brackets][sum] = true;
  if (pos == N) {
    possible[sum] = true;
    return;
  }
  sum += value[pos] * sign[pos] * (1 - 2 * (open_brackets % 2));
  if (sign[pos] == -1) {
    dp(pos + 1, open_brackets + 1, sum);
  }
  if (open_brackets > 0) {
    dp(pos + 1, open_brackets - 1, sum);
  }
  dp(pos + 1, open_brackets, sum);
}

int main() {
  string s;
  while (getline(cin, s)) {
    stringstream ss(s);
    int a = 1;
    ss >> value[0];
    sign[0] = 1;
    N = 1;
    char c;
    while (ss >> c) {
      a = (c == '+' ? 1 : -1);
      sign[N] = a;
      ss >> value[N]; N++;
    }
    possible.reset();
    fill(&checked[0][0][0], &checked[MAX][0][0], false);
    dp(0, 0, 2900);
    cout << possible.count() << endl;
  }
}
