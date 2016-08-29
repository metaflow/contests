#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ii = pair<int,int>;
using ll = long long;
using llu = unsigned long long;
const int INF = numeric_limits<int>::max();

int main() {
  // ios_base::sync_with_stdio(false);
  int tcc;
  scanf("%d", &tcc);
  // cin >> tcc;
  int v['Z'];
  fill(&v[0], &v['Z'], -1);
  v['0'] = 0;
  v['1'] = 1;
  v['A'] = v['B'] = v['C'] = v['2'] = 2;
  v['D'] = v['E'] = v['F'] = v['3'] = 3;
  v['G'] = v['H'] = v['I'] = v['4'] = 4;
  v['J'] = v['K'] = v['L'] = v['5'] = 5;
  v['M'] = v['N'] = v['O'] = v['6'] = 6;
  v['P'] = v['R'] = v['S'] = v['7'] = 7;
  v['T'] = v['U'] = v['V'] = v['8'] = 8;
  v['W'] = v['X'] = v['Y'] = v['9'] = 9;
  int* count = new int[10000000];
  int a[50000]; int pa;
  char str[250];
  while (tcc--) {
    int n;
    pa = 0;
    scanf("%d", &n);
    string s;
    fill_n(count, 10000000, 0);
    bool f = false;
    while (n--) {
      // cin >> s;
      scanf("%s", str);
      int p = 0;
      for (char c : str) {
        if (c == 0) break;
        if (c == '-') continue;
        p = p * 10 + v[c];
      }
      count[p]++;
      if (count[p] == 2) {
        a[pa] = p; pa++;
      }
      // cerr << p << endl;
    }
    if (pa) {
      sort(a, a + pa);
      for (int i = 0; i < pa; i++) {
        printf("%03d-%04d %d\n", a[i] / 10000, a[i] % 10000, count[a[i]]);
      }
    } else {
      printf("No duplicates.\n");
    }
    if (tcc) printf("\n");
  }
}
