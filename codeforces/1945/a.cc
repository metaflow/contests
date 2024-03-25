#include <iostream>

using namespace std;
using l = long long;

int main() {
  l n;
  cin >> n;
  while (n--) {
    int a, b, c;
    cin >> a >> b >> c;
    l t = ((b + c) % 3);
    if (t > c) {
      cout << -1 << '\n';
      continue;
    }
    cout << (a + (b + c + 2) / 3) << '\n';
  }
}
