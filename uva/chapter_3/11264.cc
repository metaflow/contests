#include <iostream>
#include <vector>
using namespace std;

int main() {
    int tcc;
    scanf("%d", &tcc);
    while (tcc--) {
        int n;
        cin >> n;
        int p = 0;
        int r = 0;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int v;
            scanf("%d", &v);
            if (p + sum < v) {
                sum += p;
                r++;
            }
            p = v;
        }
        cout << r << endl;
    }
    return 0;
}
