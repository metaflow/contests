#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> names(n);
    for (int i = 0; i < n; i++) cin >> names[i];
    string song[16] = {"Happy", "birthday", "to", "you", "Happy", "birthday", "to", "you", "Happy", "birthday", "to", "Rujia", "Happy", "birthday", "to", "you"};
    int k = 0;
    while (k < n) {
        for (int i = 0; i < 16; i++, k++) {
            printf("%s: %s\n", names[k % n].c_str(), song[i].c_str());
        }
    }
    return 0;
}
