#include <iostream>

using namespace std;
using l = long long;

int main() {
  l n;
  cin >> n;
  while (n--) {
    l a, b, m;
    cin >> a >> b >> m;
    cout << (m / a + m / b + 2) << '\n';
  }
}
