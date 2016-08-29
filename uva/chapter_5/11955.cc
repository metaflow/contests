#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

const int MAX = 51;

llu coeff[MAX][MAX];

void init_coeff() {
  for (int i = 0; i < MAX; i++) {
    coeff[i][0] = 1;
    coeff[i][i] = 1;
    for (int j = 1; j < i; j++) {
      coeff[i][j] = coeff[i - 1][j - 1] + coeff[i - 1][j];
    }
  }
}

int main() {
  int tcc;
  init_coeff();
  cin >> tcc;
  for (int tc = 1; tc <= tcc; tc++) {
    printf("Case %d: ", tc);
    string s;
    cin >> s;
    int pos = s.find("+");
    string a = s.substr(1, pos - 1);
    string b = s.substr(pos + 1, s.find(")") - pos - 1);
    string c = s.substr(s.find("^") + 1);
    int k = stoi(c);
    for (int i = 0; i <= k; i++) {
      if (i) printf("+");
      int pa = k - i;
      int pb = i;
      auto c = coeff[k][i];
      if (c > 1) printf("%llu*", c);
      if (pa != 0) {
        printf("%s", a.c_str());
        if (pa > 1) printf("^%d", pa);
        if (pb != 0) printf("*");
      }
      if (pb != 0) {
        printf("%s", b.c_str());
        if (pb > 1) printf("^%d", pb);
      }
    }
    printf("\n");
  }
}

//time 26m
