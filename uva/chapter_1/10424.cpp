#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

float get_score(string &a) {
    int r = 0;
    for (int i = 0; i < a.size(); i++) {
        char c = a[i];
        if (c >= 'a' && c <= 'z') r += c - 'a' + 1;
        if (c >= 'A' && c <= 'Z') r += c - 'A' + 1;
    }
    r %= 9;
    if (r == 0) r = 9;
    return 1.0 * r;
}

int main() {
    string a, b;
    while (!cin.eof()) {
        getline(cin, a);
        if (cin.eof()) return 0;
        getline(cin, b);
        float sa = get_score(a);
        float sb = get_score(b);
        float r = min(sa, sb) / max(sa, sb);
        printf("%.2f %%\n", r * 100);
    }
    return 0;
}
