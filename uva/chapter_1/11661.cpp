#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int n;
    while (cin >> n, n != 0) {
        string s;
        cin >> s;
        int r = -n;
        int d = -n;
        int m = n;
        for (int i = 0; i < s.size(); i++) {
            switch(s[i]) {
                case 'R': r = i;
                          m = min(m, r - d);
                          break;
                case 'D': d = i;
                          m = min(m, d - r);
                          break;
                case 'Z': m = 0;
                          break;
            }
        }
        cout << m << endl;
    }
    return 0;
}
