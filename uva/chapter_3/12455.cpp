#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, p;
        cin >> n >> p;
        int v[n];
        for (int i = 0; i < p; i++) {
            cin >> v[i];
        }
        int m;
        for (m = 0; m < (1 << p); m++) {
            int s = 0;
            for (int j = 0; j < p; j++) {
                if (m & (1 << j)) s += v[j];
            }
            if (s == n) break;
        }
        if (m < (1 << p)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
