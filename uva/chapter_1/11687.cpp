#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    while (cin >> s && s != "END") {
        int r = 4;
        if (s.size() < 10) {
            if (s.size() < 2) {
                if (s != "1") {
                    r = 2;
                } else {
                    r = 1;
                }
            } else {
                r = 3;
            }
        }
        cout << r << endl;
    }
    return 0;
}
