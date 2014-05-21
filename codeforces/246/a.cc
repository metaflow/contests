#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int c = 0;
    while (n--) {
        int v;
        cin >> v;
        if (v + k <= 5) c++;
    }
    cout << (c / 3) << endl;
}
