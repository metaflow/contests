#include <iostream>
#include <string>

using namespace std;

int main() {
    int cas;
    scanf("%d\n", &cas);
    while (cas--) {
        string s;
        getline(cin, s);
        int b = 0, p = 0;
        for (auto it = s.begin(); it != s.end(); it++) {
            if (*it == 'M') {
                b++;
                p++;
            }
            if (*it == 'F') {
                b--;
                p++;
            }
        }
        if (b == 0 && p > 2) {
            printf("LOOP\n");
        } else {
            printf("NO LOOP\n");
        }
    }
    return 0;
}
