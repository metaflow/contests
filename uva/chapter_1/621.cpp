#include <iostream>
#include <string>

using namespace std;

int main() {
    int case_count;
    cin >> case_count;
    while (case_count--) {
        string s;
        cin >> s;
        if (s == "1" || s == "4" || s == "78") {
            cout << "+\n";
        } else if (s.substr(s.length() - 2, 2) == "35") {
            cout << "-\n";
        } else if (s[0] == '9' && s[s.length() - 1] == '4') {
            cout << "*\n";
        } else if (s.substr(0,3) == "190") {
            cout << "?\n";
        }
    }
    return 0;
}
