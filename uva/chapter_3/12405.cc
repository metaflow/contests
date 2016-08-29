#include <iostream>
#include <string>

using namespace std;

int main() {
    int tcc;
    cin >> tcc;
    for (int tc = 1; tc <= tcc; tc++) {
        int n;
        string s;
        cin >> n >> s;
        int r = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '.') {
                r++;
                i += 2;
            }
        }
        cout << "Case " << tc << ": " << r << endl;
    }
    return 0;
}
